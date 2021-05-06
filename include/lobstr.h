#include <inttypes.h>

#ifndef LOBSTR_H_INCLUDED
#define LOBSTR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

uint8_t allocHook(void *hook, void **original);
uint8_t freeHook(void *hook, void **original);

#ifdef __cplusplus
}
#endif
#endif // LOBSTR_H_INCLUDED
