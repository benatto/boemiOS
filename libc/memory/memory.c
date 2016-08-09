#include <stddef.h>

#include <memory/memory.h>

extern unsigned long __force_order;

void write_cr3(addr_t val) {
	asm volatile ("mov %0,%%cr3": :"r" (val));
}

addr_t read_cr3(void) {
	addr_t val;
	asm volatile ("mov %%cr3, %0\n\t": "=r" (val): "m" (__force_order));
	return val;
}
