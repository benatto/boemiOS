#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void itoa(char *buf, int base, int d) {
	char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put `-' in the head. */
    if (base == 'd' && d < 0) {
      *p++ = '-';
      buf++;
      ud = -d;
	} else if (base == 'x') {
      divisor = 16;
	}

    /* Divide UD by DIVISOR until UD == 0. */
    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	}
    while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
	}
}

static void print(const char *data, size_t data_length) {
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}
 
int printf(const char *restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
 
	while (*format != '\0') {
		if (*format != '%') {
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}
 
		const char *format_begun_at = format;
 
		if (*(++format) == '%')
			goto print_c;
 
		if (rejected_bad_specifier) {
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		} else if (*format == 's') {
			format++;
			const char *s = va_arg(parameters, const char*);
			print(s, strlen(s));
		} else if (*format == 'd' || *format == 'x'
				|| *format == 'u' || *format == 'l') {
			/*TODO: When we have malloc use it here*/
			char buf[16];
			itoa(buf, *format, va_arg(parameters, int));
			print(buf, strlen(buf));
		} else {
			goto incomprehensible_conversion;
		}
	}
 
	va_end(parameters);
 
	return written;
}
