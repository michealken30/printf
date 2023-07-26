#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char – This prints a char
 * @ap: List of a arguments
 * @buffer: This buffer array handles print
 * @flags:  It calculates active flags
 * @width: get width
 * @precision: For precision specification
 * @size: For Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list ap, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(ap, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string – This prints a string
 * @ap: List of a arguments
 * @buffer: The buffer array to handle print
 * @flags:  it calculates active flags
 * @width: Width.
 * @precision:For precision specification
 * @size:For size specifier
 * Return: Number of chars printed
 */
int print_string(va_list ap, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, j;
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

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (j = width - len; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - len; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent – This prints a percent sign
 * @ap: List of a arguments
 * @buffer: A buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Width.
 * @precision: For precision specification
 * @size: For size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list ap, char buffer[],
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

/************************* PRINT INT *************************/
/**
 * print_int – This prints int
 * @ap: List of a arguments
 * @buffer: The buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: For precision specification
 * @size: For size specifier
 * Return: Number of chars printed
 */
int print_int(va_list ap, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(ap, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
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

/************************* PRINT BINARY *************************/
/**
 * print_binary – This prints an unsigned number
 * @ap: List of a arguments
 * @buffer: The buffer array to handle print
 * @flags:  For calculating active flags
 * @width: get width.
 * @precision: For precision specification
 * @size: For size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list ap, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int p, q, n, sum;
	unsigned int b[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	p = va_arg(types, unsigned int);
	q = 2147483648; /* (2 ^ 31) */
	b[0] = p / q;
	for (n = 1; n < 32; n++)
	{
		q /= 2;
		b[n] = (p / q) % 2;
	}
	for (n = 0, sum = 0, count = 0; n < 32; n++)
	{
		sum += b[n];
		if (sum || n == 31)
		{
			char y = '0' + b[n];

			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}


