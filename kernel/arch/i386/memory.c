#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot.h>
#include <kernel/memory.h>
#include <kernel/asm.h>
#include <kernel/tty.h>

#include <memory/memory.h>

static inline void _print_memmap(void) {
	uint32_t i, len;
	addr_t start_addr;

	for (i = 0; i < mem_map.size; i++) {
		len = mem_map.mmap[i].length;
		start_addr = mem_map.mmap[i].addr;

		printf("\t[0x%x-0x%x]...%u [size(B): %u]\n",
							(unsigned) start_addr,
							(unsigned) (start_addr + len),
							(unsigned) mem_map.mmap[i].type,
							(unsigned) len);
	}
}



/* Allocate size/page_size pages from physical memory
 * the memory will be allocated directly aftwards endkernel.
 * This should be used wisely and just on system's bootstrap
static void *alloc_phys(unsigned int size) {
	static uint32_t last_addr = 0;
	void *base;
	unsigned long nr_pages;

	nr_pages = 0;

	if (last_addr == 0) {
		last_addr = (uint32_t)&endkernel;
	}

	last_addr = (last_addr + (PAGE_SIZE)-1) & ~((PAGE_SIZE)-1);

	base = (void*)last_addr;

	nr_pages = size/PAGE_SIZE;

	nr_pages = size <= PAGE_SIZE ? 1 : size/PAGE_SIZE;

	last_addr += nr_pages * PAGE_SIZE;

	return base;
}*/

int meminit(multiboot_info_t *mbi) {
	unsigned int i, j;
	unsigned long zone_len;
	multiboot_memory_map_t *mmap;
	mem_zone_t *zone;

	printf("Retrieving memory information...\n");
	if (!CHECK_FLAG(mbi->flags, 0)) {
		return 1;
	}
 
	printf("\tmbi mem_lower: %uKB\n", mbi->mem_lower);
	printf("\tmbi mem_upper: %uKB\n", mbi->mem_upper);

	i = 0;

	/* We store the zone info right after the kernel ends in memory.
	 * We used this place holder as at this point we don't have a page frame
	 * allocator in place yet */
	zone = (mem_zone_t*)&endkernel;

	for (mmap = (multiboot_memory_map_t*)mbi->mmap_addr;
		(unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
		 mmap = (multiboot_memory_map_t*)((unsigned long)mmap +
							 mmap->size + sizeof(mmap->size))) {
		mem_map.mmap[i].size = mmap->size;
		mem_map.mmap[i].addr = mmap->addr;
		mem_map.mmap[i].length = mmap->len;
		mem_map.mmap[i].type = mmap->type;

		zone_len = mmap->len;
		zone->start_addr = mmap->addr;
		zone->end_addr = zone->start_addr + zone_len;
		zone->zone_len = zone_len;
		zone->zone_status = mmap->type;
		zone->nr_pages = zone->zone_len/PAGE_SIZE;
		zone->free_pages = zone->nr_pages;


		printf("Zone [0x%x-0x%x] %lu (B), %lu pages, status: %s\n",
				(unsigned int)zone->start_addr, (unsigned int)zone->end_addr,
				 zone->zone_len, zone->nr_pages,
				zone->zone_status == ZONE_AVAILABLE ? "FREE" : "RESERVED");

		for (j = 0; j < (zone->nr_pages/8); j++)
			zone->zone_bitmap[j] = 0;

		zone = zone + sizeof(mem_zone_t);
		i++;
	}

	mem_map.size = i;

	printf("End of memory map\n");

	return 0;
}


pgd_t *fill_pgtable(void) {
	int i;

	for (i = 0; i < PGD_ENTRIES; i++) {
		page_directory[i] = SWAPPER_FLAGS;
	}

	for (i = 0; i < PGD_ENTRIES; i++) {
		init_pgd[i] = (i * 0x1000) | 3;
	}

	page_directory[0] = ((pgd_t)init_pgd) | 3;

	return init_pgd;
}
