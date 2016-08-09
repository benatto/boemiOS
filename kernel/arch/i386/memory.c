#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot.h>
#include <kernel/memory.h>
#include <memory/memtypes.h>

//extern memmap mem_map;

static void _print_memmap(void) {
	uint32_t i, size;
	addr_t start_addr;

	for (i = 0; i < mem_map.size; i++) {
		size = mem_map.mmap[i].size;
		start_addr = mem_map.mmap[i].addr;

		printf("\t[0x%x-0x%x]...%u [size: %u]\n",
							(unsigned) start_addr,
							(unsigned) (start_addr + size),
							(unsigned) mem_map.mmap[i].type,
							(unsigned) size);
	}
}

int meminit(multiboot_info_t *mbi) {
	int i;
	multiboot_memory_map_t *mmap;

	printf("Retrieving memory information...\n");
	if (!CHECK_FLAG(mbi->flags, 0))
		abort();
 
	printf("\tmbi mem_lower: %uKB\n", mbi->mem_lower);
	printf("\tmbi mem_upper: %uKB\n", mbi->mem_upper);

	i = 0;

	for (mmap = (multiboot_memory_map_t*)mbi->mmap_addr;
		(unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
		 mmap = (multiboot_memory_map_t*)((unsigned long)mmap + mmap->size + sizeof(mmap->size))) {
		mem_map.mmap[i].size = mmap->size;
		mem_map.mmap[i].addr = mmap->addr;
		mem_map.mmap[i].length = mmap->len;
		mem_map.mmap[i].type = mmap->type;

		i++;
	}

	mem_map.size = i;

	_print_memmap();
	printf("End of memory map\n");

	return 0;
}
