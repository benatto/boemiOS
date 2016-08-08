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

typedef struct page {
	
}page_t;

#endif
