#include "main.h"

/**
 * print_char - it prints a char.
 * @types: list arguments.
 * @buffer: buffer array handles print
 * @flags:  it calculates active flags.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z = va_arg(types, int);

	return (handle_write_char(z, buffer, flags, width, precision, size));
}

/**
 * print_string - it prints strings.
 * @types: lists a of argument.
 * @buffer: buffer array handles print.
 * @flags:  it calculates active flags
 * @width:  width.
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
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
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - it prints percent sign.
 * @types: lists of argument.
 * @buffer: buffer array handles print.
 * @flags:  it calculates active flags.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print.
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

/**
 * print_int - it prints int
 * @types: lists of argument.
 * @buffer: Buffer arrays handles print.
 * @flags:  it calculates active flags.
 * @width:  width.
 * @precision: Precision.
 * @size: Size.
 * Return: number chars to print
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_size_number(m, size);

	if (m == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - it prints an unsigned numbers.
 * @types: lists of argument.
 * @buffer: buffer array handles print.
 * @flags:  it calculates active flags.
 * @width: width.
 * @precision: Precision.
 * @size: size.
 * Return: numbers of Char displayed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int k, q, j, sum;
	unsigned int a[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	k = va_arg(types, unsigned int);
	q = 2147483648; /* (2 ^ 31) */
	a[0] = k / q;
	for (j = 1; j < 32; j++)
	{
		q /= 2;
		a[j] = (k / q) % 2;
	}
	for (j = 0, sum = 0, counter = 0; j < 32; j++)
	{
		sum += a[j];
		if (sum || j == 31)
		{
			char y = '0' + a[j];

			write(1, &y, 1);
			counter++;
		}
	}
	return (counter);
}
