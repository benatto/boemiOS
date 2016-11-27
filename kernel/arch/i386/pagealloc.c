#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <kernel/pagealloc.h>
#include <kernel/memory.h>


void *get_page(unsigned long size) {
	short found;
	unsigned int nr_pages, i, free, addr;
	mem_zone_t *zone;

	found = 1;
	nr_pages = size/PAGE_SIZE;

	printf("Will allocate %u pages\n", nr_pages);

	zone = (mem_zone_t*)&endkernel;
	printf("First zone at: 0x%x\n", (unsigned int)zone);

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
