#ifndef __H_MEMTYPES_M__
#define __H_MEMTYPES_H__
#define PAGE_SHIFT 12

#define PAGE_SIZE 1UL << PAGE_SHIFT


/*Number of bits on physical addr*/

#if defined(__i386__)
#define PADDR_SIZE 2UL << 4
#define MAXMEM 2^PADDR_SIZE
#else
#error "Architecture not supported"
#endif

typedef unsigned long addr_t;

struct memmap_entry {
	addr_t addr;
	uint32_t length;
	uint32_t type;
	uint32_t size;
};

typedef struct memmap_entry map_entry;

struct memmap {
	uint32_t size;
	map_entry mmap[MAXMEM];
};

typedef struct memmap memmap;

memmap mem_map;

typedef struct page {
	
}page_t;

#endif
