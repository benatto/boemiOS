/* Some usefull ASM directive or attributes to optimization*/
#ifndef __H_ASM_H__

/*#define __init __section(.init.text)*/

/* Align to N bytes*/
#define ALIGN_TO(N) __attribute__((aligned(N)))

#endif
