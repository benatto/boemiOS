#if defined(__is_boemios_kernel)
#include <kernel/tty.h>

#include <stdio.h>

void cls(void) {
	tty_clear();
}
#endif
