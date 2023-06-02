#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @types: lists a of arguments
 * @buffer: buffer array handles print
 * @flags:  it calculates active flags
 * @width: width
 * @precision: Precision.
 * @size: Size.
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


/**
 * print_octal - it prints an unsigned number in octal notation
 * @types: lists of arguments
 * @buffer: buffer array to handle print
 * @flags:  it calculates active flags.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - it prints an unsigned number in hexadecimal notation
 * @types: Lists of arguments.
 * @buffer: buffer array handles print
 * @flags:  it calculates active flags
 * @width:  width.
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print.
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - it prints an unsigned number in upper hexadecimal notation.
 * @types: lists of arguments.
 * @buffer: buffer array to handle print
 * @flags:  it calculates active flags
 * @width:  width
 * @precision: Precision.
 * @size: Size.
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - it prints a hexadecimal number in lower or upper.
 * @types: lists of arguments
 * @map_to: Arrays of values to map the number to
 * @buffer: buffer array to handles print
 * @flags:  Calculates active flags
 * @flag_ch: it calculates active flags
 * @width:  width
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}
