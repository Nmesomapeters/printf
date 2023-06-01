#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - The Printf Function.
 * @format: The format.
 * Return: Displayedd Chars.
 */
int _printf(const char *format, ...)
{
	int m, displayed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (m = 0; format && format[m] != '\0'; m++)
	{
		if (format[m] != '%')
		{
			buffer[buff_ind++] = format[m];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/** To write(1, &format[m], 1) **/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &m);
			width = get_width(format, &m, list);
			precision = get_precision(format, &m, list);
			size = get_size(format, &m);
			++m;
			displayed  = handle_print(format, &m, list, buffer,
				flags, width, precision, size);
			if (displayed == -1)
				return (-1);
			printed_chars += displayed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - It prints the contents of the buffer if they exist.
 * @buffer: Consist of array of Chars.
 * @buff_ind: It index at which to add next char, represents the length.
 * returns void
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
