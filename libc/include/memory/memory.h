#ifndef __H_MEMORY_H__
#define __H_MEMORY_H__

#include <sys/cdefs.h>
#include <memory/memtypes.h>

void write_cr3(addr_t val);
addr_t read_cr3(void);

#endif
