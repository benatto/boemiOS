#ifndef __H_MEMORY_H__
#define __H_MEMORY_H__

#include <boot/multiboot.h>

typedef uint32_t pgd_t;

int meminit(multiboot_info_t*);
pgd_t *fill_pgtable(void);
#endif
