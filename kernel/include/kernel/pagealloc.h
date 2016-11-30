#ifndef __H_PAGEALLOC_H__
#define __H_PAGEALLOC_H__

void *get_page(unsigned long size);
void free_page(void *p);
void free_page_range(void *start, unsigned long len);

#endif
