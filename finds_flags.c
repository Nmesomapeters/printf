#include "main.h"

/**
 * get_flags - calculates for active flags
 * @format: format.
 * @i: Takes in parameter
 * Return: flags.
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_x;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_x = *i + 1; format[curr_x] != '\0'; curr_x++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_x] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_x - 1;

	return (flags);
}
