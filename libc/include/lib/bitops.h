#ifndef __H_BITOPS_H__
#define __H_BITOPS_H__

#define test_bit(v, bit)(*v) & (1 << bit)

#define set_bit(v, bit)	(*v) |= (1 << bit)

#define clear_bit(v, bit) (*v) ^= (1 << bit)

#endif
