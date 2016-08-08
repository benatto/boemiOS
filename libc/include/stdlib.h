#ifndef _STDLIB_H
#define _STDLIB_H 1
 
#include <sys/cdefs.h>

#if defined(__is_boemios_kernel)

#define ABORT_ON(C) if(C) { abort(); }

__attribute__((__noreturn__))
void abort(void);
#else
void abort(void) { do{}while(0); }
 
#endif
#endif
