#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot.h>
#include <kernel/memory.h>
#include <memory/memtypes.h>

int meminit(multiboot_info_t *mbi) {
	if (!CHECK_FLAG(mbi->flags, 0))
		abort();
 
	 printf("mbi mem_lower: %uKB\n", mbi->mem_lower);
	 printf("mbi mem_upper: %uKB\n", mbi->mem_upper);
	return 0;
}
