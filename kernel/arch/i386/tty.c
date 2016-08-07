#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/*#include <string.h>*/
 
#include <kernel/tty.h>
#include <kernel/vga.h>
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void tty_init(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void print_char(char c) {
	enum special_char sc;

	sc = (enum special_char)c;

	switch(sc) {
		case CHAR_TAB:
			terminal_column += TABCOUNT;
			return;
		case CHAR_NEWLINE: /*\n increments line and do a CHAR_RETURN*/
			terminal_row++;
		case CHAR_RETURN:
			terminal_column = 0;
			return;
		case CHAR_BLANK:
			terminal_column++;
		default: /* If the special char doesn't match anything we don't print*/
			break;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row = 0;
		}
	}
}
 
void tty_write(const char *data, size_t size) {
	for ( size_t i = 0; i < size; i++ )
		print_char(data[i]);
}
 
void tty_writestring(const char *data) {
	tty_write(data, strlen(data));
}
