#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <capstone/capstone.h>

#define PLAT_WINDOWS defined _WIN32 || defined _WIN64
#define PLAT_UNIX defined __unix__
#define ARCH_ARM defined _M_ARM || defined __arm__
#define ARCH_ARM64 defined __aarch64__
#define ARCH_X32 defined _M_IX86 || defined __i386__
#define ARCH_X64 defined _M_X64 || defined __amd64__

#if PLAT_WINDOWS
#include <windows.h>
#define EXPORT __declspec(dllexport)
#define werror(function) { \
	char *errorMessage = NULL; \
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), &errorMessage, 0, NULL); \
	fprintf(stderr, function ": %s\r\n", errorMessage); \
	LocalFree(errorMessage); \
}

#elif PLAT_UNIX
#include <dlfcn.h>
#include <sys/mman.h>
#include <unistd.h>

#define EXPORT
#else
#error "Only Windows (x32/x64) and Unix (x32/x64) targets are supported"
#endif // PLAT_WINDOWS

#if ARCH_ARM || ARCH_ARM64
#error "ARM not yet supported"
#elif ARCH_X32
#define JUMP(variable, address) \
	uint8_t variable[] = { \
		0x68, 0x00, 0x00, 0x00, 0x00, /* mov rax, 0x0 */ \
		0xc3                          /* jmp rax */ \
	}; \
	\
	*(void **)((uintptr_t)&variable + 1) = address;
#elif ARCH_X64
#define JUMP(variable, address) \
	uint8_t variable[] = { \
		0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* mov rax, 0x0 */ \
		0xff, 0xe0                                                  /* jmp rax */ \
	}; \
	\
	*(void **)((uintptr_t)&variable + 2) = address;
#endif // ARCH_ARM || ARCH_ARM64

enum protection {
	READ = 1,
	WRITE = 1 << 1,
	EXECUTE = 1 << 2
};

uint8_t changeProtection(void *address, uintmax_t size, uint8_t protection) {
	#if PLAT_WINDOWS
	uintptr_t pageSize;
	{
    	SYSTEM_INFO info;
    	GetSystemInfo(&info);
		pageSize = info.dwPageSize;
	}
	#elif PLAT_UNIX
	uintptr_t pageSize = sysconf(_SC_PAGESIZE);
	#endif

	uintptr_t pagedAddress = (uintptr_t)address - ((uintptr_t)address % pageSize);

	#if PLAT_WINDOWS
	int platformProtection = PAGE_NOACCESS;
	switch (protection) { // Refer to https://docs.microsoft.com/en-us/windows/win32/memory/memory-protection-constants
		case EXECUTE: platformProtection = PAGE_EXECUTE; break; // 0b100
		case READ | EXECUTE: platformProtection = PAGE_EXECUTE_READ; break; // 0b101
		case READ | WRITE | EXECUTE: platformProtection = PAGE_EXECUTE_READWRITE; break; // 0b111
		case 0: platformProtection = PAGE_NOACCESS; break; // 0b000
		case READ: platformProtection = PAGE_READONLY; break; // 0b001
		case READ | WRITE: platformProtection = PAGE_READWRITE; break; // 0b011
		default: return 1;
	}

	int ignored;
	if (VirtualProtect((void *)pagedAddress, pageSize, platformProtection, &ignored) == 0) {
		werror("VirtualProtect")
		return 1;
	}
	#elif PLAT_UNIX
	int platformProtection = (!!(protection & READ) * PROT_READ) | (!!(protection & WRITE) * PROT_WRITE) | (!!(protection & EXECUTE) * PROT_EXEC);
	if (mprotect((void *)pagedAddress, pageSize, platformProtection)) {
		perror("mprotect");
		return 1;
	}
	#endif

	return 0;
}

uintptr_t getInstructionSizeForMinimum(void *buffer, uintmax_t minimum) {
	csh handle;

	enum {
		#if ARCH_X32
		CS_ARCH = CS_ARCH_X86,
		CS_MODE = CS_MODE_32,
		#elif ARCH_X64
		CS_ARCH = CS_ARCH_X86,
		CS_MODE = CS_MODE_64,
		#elif ARCH_ARM
		CS_ARCH = CS_ARCH_ARM,
		CS_MODE = CS_MODE_ARM,
		#elif ARCH_ARM64
		CS_ARCH = CS_ARCH_ARM64,
		CS_MODE = CS_MODE_ARM,
		#endif
	};

	if (cs_open(CS_ARCH, CS_MODE, &handle) != CS_ERR_OK)
		return 0;

	uintptr_t finalSize = 0;
	while (finalSize < minimum) {
		cs_insn *instruction;
		uintmax_t instructionCount;
		uint8_t instructionSize = 0;

		while ((instructionCount = cs_disasm(handle, (void *)((uintptr_t)buffer + finalSize), ++instructionSize, 0, 1, &instruction)) != 1)
			cs_free(instruction, instructionCount);

		finalSize += instructionSize;
	}

	cs_close(&handle);

	return finalSize;
}

uint8_t freeMap(void *map, uintmax_t size) {
	#if PLAT_WINDOWS
	if (VirtualFree(map, size, MEM_DECOMMIT) == 0) {
		werror("VirtualFree")
		return 1;
	}
	#elif PLAT_UNIX
	if (munmap(map, size) != 0) {
		perror("munmap");
		return 1;
	}
	#endif

	return 0;
}

void *allocateTrampoline(void *buffer, uintptr_t bufferSize) {
	JUMP(origContinuationJumpPatch, (void *)((uintptr_t)buffer + bufferSize))

	uintmax_t fullSize = bufferSize + sizeof(origContinuationJumpPatch);


	#if PLAT_WINDOWS
	void *trampoline = VirtualAlloc(NULL, fullSize, MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);

	if (trampoline == NULL) {
		werror("VirtualAlloc")
		return NULL;
	}
	#elif PLAT_UNIX
	FILE *fp = fopen("/dev/zero", "rb");
	if (!fp)
		return NULL;

	int fd = fileno(fp);

	if (fd == -1) {
		fclose(fp);
		return NULL;
	}

	void *trampoline = mmap(NULL, fullSize, PROT_NONE, MAP_PRIVATE, fd, 0);

	fclose(fp);

	if (trampoline == MAP_FAILED) {
		perror("mmap");
		return NULL;
	}
	#endif

	if (changeProtection(trampoline, fullSize, READ | WRITE | EXECUTE)) {
		freeMap(trampoline, fullSize);
		return NULL;
	}

	memcpy(trampoline, buffer, bufferSize);
	memcpy((void *)((uintptr_t)trampoline + bufferSize), origContinuationJumpPatch, sizeof(origContinuationJumpPatch));

	return trampoline;
}

EXPORT uint8_t allocHook(void *hook, void **original) {
	if (hook == NULL || original == NULL)
		return 1;

	JUMP(hookJumpPatch, hook)

	if (changeProtection(*original, sizeof(hookJumpPatch), READ | WRITE | EXECUTE))
		return 1;

	const uintptr_t instructionSizes = getInstructionSizeForMinimum(*original, sizeof(hookJumpPatch));
	if (instructionSizes == 0)
		return 1;

	void *trampoline = allocateTrampoline(*original, instructionSizes);
	if (trampoline == NULL)
		return 1;

	memcpy(*original, &hookJumpPatch, sizeof(hookJumpPatch));

	*original = trampoline;


	return 0;
}

EXPORT uint8_t freeHook(void *hook, void **original) {
	return 0;
}
