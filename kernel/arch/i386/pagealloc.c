#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <kernel/pagealloc.h>
#include <kernel/memory.h>

void free_page(void *p) {
	unsigned int addr, i, offset;
	mem_zone_t *zone;

	offset = 0;
	addr = (unsigned int)p;
	zone = (mem_zone_t*)&endkernel + sizeof(mem_zone_t);

	for (i = 0; i < zone_nr; i++, zone = zone + sizeof(mem_zone_t)) {
		if (addr >= zone->start_addr && addr < zone->end_addr)
			goto found_zone;
	}

	printf("Invalid memory operation at: 0x%x\n", addr);
	abort();

found_zone:
	offset = (addr - zone->start_addr)/PAGE_SIZE;
	zone->zone_bitmap[offset] = 0;
	zone->free_pages++;
	ABORT_ON(zone->free_pages > zone->nr_pages);
}

void free_page_range(void *start, unsigned long len) {
	unsigned int i, nr_pages;
	void *p;

	p = start;

	nr_pages = len/PAGE_SIZE;

	for (i = 0; i < nr_pages; i++, p = p + PAGE_SIZE) {
		free_page(p);
	}
}

void *get_page(unsigned long size) {
	short found;
	unsigned int nr_pages, i, free, addr;
	mem_zone_t *zone;

	found = 1;
	nr_pages = size/PAGE_SIZE;

	zone = (mem_zone_t*)&endkernel + sizeof(mem_zone_t);

	i = 0;
	while (i < zone_nr) {
		if (zone->zone_status == ZONE_RESERVED) {
			/*printf("Escaping zone %d, reserved [0x%x]\n", i,
										(unsigned int)zone);*/
			goto next;
		}

		if (zone->free_pages > nr_pages) {
			/*printf("Found zone: %d, addr: 0x%x\n", i, (unsigned int)zone);*/
			break;
		} else {
			printf("Zone: %d is too small\n", i);
		}
next:
		i++;
		zone = zone + sizeof(mem_zone_t);
	}

	/* We first try to go at the last free position */
	free = zone->free_page;

	/* nr_pages contiguous pages should be available */
	for (i = free; i < free + nr_pages; i++) {
		if (zone->zone_bitmap[i] == 1) {
			found = 0;
		}
	}

	if (!found)
		return NULL;

	addr = zone->start_addr + (free * PAGE_SIZE);

	for (i = free; i < free + nr_pages; i++)
		zone->zone_bitmap[i] = 1;
	
	zone->free_page = free + nr_pages + 1;
	zone->free_pages -= nr_pages;

	return (void*)addr;
}
