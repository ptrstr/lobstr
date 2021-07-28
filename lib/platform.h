#ifndef _PLATFORM_H
#define _PLATFORM_H

#if defined _WIN32 || defined _WIN64
#	define PLAT_WINDOWS	1
#	define PLAT_UNIX	0
#elif defined __unix__
#	define PLAT_WINDOWS	0
#	define PLAT_UNIX	1
#else
#	define PLAT_WINDOWS	0
#	define PLAT_UNIX	0
#	error "Only Windows and Unix platforms are supported"
#endif // defined _WIN32 || defined _WIN64

#if defined _M_ARM || defined __arm__
#	define ARCH_ARM		1
#	define ARCH_ARM64	0
#	define ARCH_X32		0
#	define ARCH_X64		0
#elif defined __aarch64__
#	define ARCH_ARM		0
#	define ARCH_ARM64	1
#	define ARCH_X32		0
#	define ARCH_X64		0
#elif defined _M_IX86 || defined __i386__
#	define ARCH_ARM		0
#	define ARCH_ARM64	0
#	define ARCH_X32		1
#	define ARCH_X64		0
#elif defined _M_X64 || defined __amd64__
#	define ARCH_ARM		0
#	define ARCH_ARM64	0
#	define ARCH_X32		0
#	define ARCH_X64		1
#else
#	define ARCH_ARM		0
#	define ARCH_ARM64	0
#	define ARCH_X32		0
#	define ARCH_X64		0
#	error "Only ARM, ARM64, x86 and x86_64 platforms are supported"
#endif // defined _M_ARM || defined __arm__

#endif
