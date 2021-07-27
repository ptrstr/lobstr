#include <inttypes.h>

#ifndef LOBSTR_H_INCLUDED
#define LOBSTR_H_INCLUDED

typedef struct _hook_t {
	void *original;
	void *trampoline;
	uintmax_t trampolineSize;
	uintmax_t trampolineJumpSize;
} hook_t;

#ifdef __cplusplus
extern "C" {
#endif

hook_t *allocHook(void *hook, void **original);
void freeHook(hook_t *hookCtx);

#ifdef __cplusplus
}
#endif
#endif // LOBSTR_H_INCLUDED
