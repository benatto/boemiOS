#ifndef __H_TTY_H__
#define __H_TTY_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#define TABCOUNT 1 << 2

enum special_char {
	CHAR_NEWLINE = '\n',
	CHAR_TAB = '\t',
	CHAR_BLANK = '\b',
	CHAR_RETURN = '\r'
};

void tty_init(void);
void print_char(char c);
void tty_writestring(const char *c);
void tty_write(const char *c, size_t data);
void tty_setcolor(uint8_t color);
void tty_clear(void);

#endif
