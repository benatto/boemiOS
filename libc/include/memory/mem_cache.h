#ifndef __H_MEM_CACHE_H__
#define __H_MEM_CACHE_H__

#include <lib/list.h>

#define MEM_CACHE_META_SIZE(m) sizeof(m)

typedef unsigned int offset_t;

typedef struct mem_cache {
	/* Cache's name*/
	char name[32];
	/* Total cache len */
	size_t len;
	/* Start addr */
	unsigned long start_addr;
	/* Bitmap of free slots */
	unsigned int bitmap;
	/* Amount of free objects */
	unsigned long free_objs;
	/* Total objects */
	unsigned total_objs;
	/* Object size */
	size_t obj_size;
	/* Next free slot */
	unsigned long free_addr;
}mem_cache_t;

enum malloc_flags {
	/* The malloc data has being initialized */
	MALLOC_INITIALIZED = 0,
	/* The malloc data is valid */
	MALLOC_VALID,
	/* malloc still has space to provide memory */
	MALLOC_HAS_SPACE,
	/* malloc can allocate more pages */
	MALLOC_CAN_ALLOC
};

typedef struct malloc_data {
	/* Total number of pages used */
	unsigned long num_pages;
	/* Current page from where pages are being allocated */
	void *current_page;
	/* Current offset for the current page */
	offset_t offset;
	/* List of pages being used */
	list_head pages;
	/* malloc data flags */
	unsigned int flags;
}malloc_data_t;

typedef struct malloc_page {
	/* Keep this struct linked on page list */
	list_head *list;
	/* Base addr */
	void *addr;
}malloc_page_t;


/* global malloc data */
malloc_data_t mdata;

/*
 * mem_cache_create: Creates a new memory cache object
 * name: cache name
 * len: total len for this cache
 */
void *mem_cache_create(char *name, size_t len);

void *malloc(size_t len);

#endif
