#include "main.h"

/**
 * print_pointer - it prints a pointer variable
 * @types: Lists a of argument.
 * @buffer: buffer array handles print.
 * @flags:  it calculates active flags
 * @width:  width.
 * @precision: Precision.
 * @size: Size.
 * Return: number of chars to print
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long number_address;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	number_address = (unsigned long)addrs;

	while (number_address > 0)
	{
		buffer[ind--] = map_to[number_address % 16];
		number_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - it prints ASCII codes in hexa of non printable chars
 * @types: Lists of argument.
 * @buffer: buffer array handles print
 * @flags:  it calculates for active flags
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * Return: number of chars to print
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = 0, offsets = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[j] != '\0')
	{
		if (is_printable(str[j]))
			buffer[j + offsets] = str[j];
		else
			offsets += append_hexa_code(str[j], buffer, j + offsets);

		j++;
	}

	buffer[j + offsets] = '\0';

	return (write(1, buffer, j + offsets));
}

/**
 * print_reverse - it prints reverse string.
 * @types: lists of arguments.
 * @buffer: buffer array handles print
 * @flags:  it calculates active flags
 * @width:  width.
 * @precision: Precision.
 * @size: Size.
 * Return: numbers of chars displayed.
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char y = str[i];

		write(1, &y, 1);
		counter++;
	}
	return (counter);
}

/**
 * print_rot13string - it prints string in rot13.
 * @types: Lists of argument.
 * @buffer: buffer array handles print
 * @flags:  it calculates active flags.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * Return: numbers chars to print.
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z;
	char *str;
	unsigned int m, n;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for ( m = 0; str[m]; m++)
	{
		for (n = 0; in[n]; n++)
		{
			if (in[n] == str[m])
			{
				z = out[n];
				write(1, &z, 1);
				counter++;
				break;
			}
		}
		if (!in[n])
		{
			z = str[m];
			write(1, &x, 1);
			counter++;
		}
	}
	return (counter);
}
