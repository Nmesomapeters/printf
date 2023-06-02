#include "main.h"

/**
 * get_size - it calculates the size to cast the argument.
 * @format: Format
 * @i: lists of arguments to print.
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int curr_x = *i + 1;
	int size = 0;

	if (format[curr_x] == 'l')
		size = S_LONG;
	else if (format[curr_x] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_x - 1;
	else
		*i = curr_x;

	return (size);
}
