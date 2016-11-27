#ifndef __H_MEMTYPES_M__
#define __H_MEMTYPES_H__

#include <kernel/asm.h>

#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define PAGE_MASK (~(PAGE_SIZE-1))


/*Number of bits on physical addr*/

#if defined(__i386__)
#define PADDR_SIZE 2UL << 4
#define MAXMEM 2^PADDR_SIZE
#define PGD_ENTRIES 1024
#define SWAPPER_FLAGS 0x00000002

#define PAGE_ALIGN(addr) (((addr)+PAGE_SIZE-1) & PAGE_MASK)

#else
#error "Architecture not supported"
#endif

typedef unsigned long addr_t;
typedef unsigned long pgd_t;

struct memmap_entry {
	addr_t addr;
	unsigned long length;
	unsigned long type;
	unsigned long size;
};

typedef struct memmap_entry map_entry;

struct memmap {
	unsigned long size;
	map_entry mmap[MAXMEM];
};

typedef struct memmap memmap;

memmap mem_map;

typedef struct page {
	
}page_t;


/*Swapper DIR and kernel pgtable won't be available to userland*/
#if defined (__is_boemios_kernel)
/* TODO: This is a temporary trick to use paging
 * 		 I really need to write a page frame allocator ASAP. 
 * 		 'till there no dynamic allocations can be done!!!*/
pgd_t page_directory[PGD_ENTRIES] ALIGN_TO(PAGE_SIZE);
pgd_t init_pgd[PGD_ENTRIES] ALIGN_TO(PAGE_SIZE);
#endif

#endif
