#include "main.h"

/** dispays char **/

/**
 * print_char - to print char
 * @types: List a of arguments
 * @buffer: buffer array to handle print
 * @flags:  to calculate active flags
 * @width: find width
 * @precision: Precision
 * @size: size
 * Return: the number of chars displayed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char f = va_arg(types, int);

	return (handle_write_char(f, buffer, flags, width, precision, size));
}
/** to display a string **/
/**
 * print_string - to print strings
 * @types: list a of arguments
 * @buffer: buffer array to handle print
 * @flags: it calculates active flags
 * @width: find width.
 * @precision: Precision.
 * @size: size
 * Return: the number of chars displayed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/** displays percent sign **/
/**
 * print_percent - to print percent sign
 * @types: lista of Arguments
 * @buffer: buffer array to handle prints
 * @flags:  it calculates active flags
 * @width: find width.
 * @precision: Precision.
 * @size: size specifier.
 * Return: The number of chars displayed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* Diplays int */
/**
 * print_int - to Print int
 * @types: lista of Arguments
 * @buffer: The buffer array to handle print
 * @flags:  calculates active flags.
 * @width: find width.
 * @precision: The precision.
 * @size: The size specifier.
 * Return:The Number of chars displayed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int z = va_arg(types, long int);
	unsigned long int number;

	z = convert_size_number(z, size);

	if (z == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)z;

	if (z < 0)
	{
		number = (unsigned long int)((-1) * z);
		is_negative = 1;
	}

	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/* for displaying unsigned binary */
/**
 * print_binary - it prints an unsigned numbers.
 * @types: lista of Arguments
 * @buffer: buffer array for handling print.
 * @flags:  it calculates active flags
 * @width: find width.
 * @precision: The precision.
 * @size: The size specifier.
 * Return: numbers of Chars diplayed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int b, a, j, sum;
	unsigned int k[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	b = va_arg(types, unsigned int);
	a = 2147483648; /* (2 ^ 31) */
	k[0] = b / a;
	for (j = 1; j < 32; j++)
	{
		a /= 2;
		k[i] = (b / a) % 2;
	}
	for (j = 0, sum = 0, counter = 0; j < 32; j++)
	{
		sum += k[j];
		if (sum || j == 31)
		{
			char q = '0' + k[j];

			write(1, &q, 1);
			counter++;
		}
	}
	return (counter);
}
