import sys

if __name__ == '__main__':
	if len(sys.argv) != 2:
		print('Usage: %s MAX' % (sys.argv[0]))
		exit(1)

	max = int(sys.argv[1])
	f = open('registers.h', 'w')

	f.write('#define CONCAT(a, b) a##b\n\n#define ARG(N, ...) ARG_##N(__VA_ARGS__)\n\n')

	for i in range(max):
		f.write('#define ARG_%d(%s, ...) _%d\n' % (i + 1, ', '.join(['_%d' % (j + 1) for j in range(i + 1)]), i + 1))

	f.write('\n')
	f.write('#define COUNT_N(%s, N, ...) N\n' % (', '.join(['_%d' % (i + 1) for i in range(max)])))
	f.write('#define COUNT(...) COUNT_N(__VA_ARGS__, %s)\n' % (', '.join([str(i + 1) for i in reversed(range(max))])))

	f.write('\n#define STRUCT_ITEMS(...) STRUCT_ITEMS_N(COUNT(__VA_ARGS__), __VA_ARGS__)\n#define STRUCT_ITEMS_N(N, ...) CONCAT(STRUCT_ITEMS_, N)(__VA_ARGS__)\n')

	for i in range(0, max + 1, 2):
		f.write('#define STRUCT_ITEMS_%d(...) %s\n' % (i if i else 1, '; '.join(['ARG(%d, __VA_ARGS__) ARG(%d, __VA_ARGS__)' % (j + 1, j + 2) for j in range(0, i, 2)]) + ';'))

	f.write('\n')

	f.write('\n#define DISTRIBUTED_CALL(FN, ...) DISTRIBUTED_CALL_N(FN, COUNT(__VA_ARGS__), __VA_ARGS__)\n#define DISTRIBUTED_CALL_N(FN, N, ...) CONCAT(DISTRIBUTED_CALL_, N)(FN, __VA_ARGS__)\n')

	for i in range(0, max + 1, 2):
		f.write('#define DISTRIBUTED_CALL_%d(FN, ...) %s\n' % (i if i else 1, ' '.join(['FN(ARG(%d, __VA_ARGS__))' % (j + 1) for j in range(1, i, 2)])))

	f.write('\n')
	f.write('#define USE_REGS(...) \\\n')
	f.write('static struct {STRUCT_ITEMS(__VA_ARGS__)} registers; \\\n')
	f.write('void registers_get() {DISTRIBUTED_CALL(LOAD_REG, __VA_ARGS__)} \\\n')
	f.write('void registers_set() {DISTRIBUTED_CALL(SAVE_REG, __VA_ARGS__)}\n')

	f.write('#define SAVE_REG(to_expand)  _SAVE_REG(to_expand)\n')
	f.write('#define _SAVE_REG(reg) asm("mov %0, %%" #reg ";" : : "m" (registers.reg));\n')
	f.write('#define LOAD_REG(to_expand) _LOAD_REG(to_expand)\n')
	f.write('#define _LOAD_REG(reg) asm("mov %%" #reg ", %0;" : "=m" (registers.reg));\n')

	f.close()
