#ifndef __H_MEMORY_H__
#define __H_MEMORY_H__

#include <boot/multiboot.h>

#include <memory/memtypes.h>

#define BITMAP_SIZE (MAXMEM)/8

typedef uint32_t pgd_t;

/* This variable marks which address in physical ram
 * the kernel ends. It has no usefull value itself,
 * what we're interest is where it's stored at memory.*/
extern unsigned int endkernel;

enum memzone_status {
	ZONE_AVAILABLE = 1,
	ZONE_RESERVED
};


/* This used to setup the page frame allocator
 * We keep these page aligned*/
typedef struct mem_zone {
	addr_t start_addr;
	addr_t end_addr;
	unsigned long nr_pages;
	unsigned long free_pages;
	/* Zone lenght in BYTES*/
	unsigned long zone_len;
	/* TODO: This really needs to be optimized
	 * we waste tons of memory here */
	unsigned int zone_bitmap[BITMAP_SIZE];
	/* zone_status indicates if the zone is available ou reserved
	 * according with the multiboot memmap	*/
	enum memzone_status zone_status;
}mem_zone_t ALIGN_TO(PAGE_SIZE);

unsigned int *freemap;

int meminit(multiboot_info_t*);
pgd_t *fill_pgtable(void);
#endif
