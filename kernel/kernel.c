#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/memory.h>

#include <boot/multiboot.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

static void __show_welcome() {
	tty_setcolor(COLOR_GREEN);
	printf("Welcome to BoemiOS\n");
	tty_setcolor(COLOR_MAGENTA);
	printf("Initializing...\n");
}

 
void kernel_early(unsigned long magic, unsigned long addr) {
	int ret;
	multiboot_info_t *mbi;
	tty_init();

	__show_welcome();

	tty_setcolor(COLOR_LIGHT_GREY);
	
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		tty_setcolor(COLOR_RED);
		printf("Invalid magic number: 0x%x\n", (unsigned int)magic);
		abort();
	}


	mbi = (multiboot_info_t*)addr;

	if (!mbi) {
		tty_setcolor(COLOR_RED);
		printf("Could not retrieve MBInfo\n");
		abort();
	}

	ret = meminit(mbi);

	ABORT_ON(ret != 0);
}

void kernel_main(void) {
	tty_setcolor(COLOR_MAGENTA);
	printf("Done.\n");
}
