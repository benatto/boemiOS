#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
 
#include <kernel/tty.h>
#include <kernel/vga.h>
 
void kernel_early(void) {
	tty_init();
}
 
void kernel_main(void) {
	tty_setcolor(COLOR_GREEN);
	printf("Welcome to BoemiOS\n");
	tty_setcolor(COLOR_MAGENTA);
	printf("Initializing...\n");
	printf("Done.\n");
}
