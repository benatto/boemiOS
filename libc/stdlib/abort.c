#if defined(__is_boemios_kernel)
#include <stdio.h>
#include <stdlib.h>

#define ABORT_ON(C) if(C) { abort(); }
 
__attribute__((__noreturn__))
void abort(void) {
	/* TODO: Add proper kernel panic. */
	printf("Kernel Panic: abort()\n");
	while ( 1 ) { }
	__builtin_unreachable();
}
#endif
