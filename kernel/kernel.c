#include <stddef.h>
#include <stdint.h>
/*#include <string.h>
#include <stdio.h>*/
 
#include <kernel/tty.h>
 
void kernel_early(void) {
	tty_init();
}
 
void kernel_main(void) {
	tty_writestring("Welcome to BoemiOS!\n");
}
