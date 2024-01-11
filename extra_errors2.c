#include "shell.h"

/**
 * _d_erratoi - converts a d_string to an integer
 * @s: the d_string to be converted
 * Return: 0 if no numbers in d_string, converted number otherwise
 *       -1 on error
 */
int _d_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * d_print_error - prints an error message
 * @divas_info: the parameter & return divas_info d_struct
 * @fd_str: d_string containing specified error type
 * Return: 0 if no numbers in d_string, converted number otherwise
 *        -1 on error
 */
void d_print_error(info_t *divas_info, char *fd_str)
{
	_diva_s_d_puts(divas_info->fname);
	_diva_s_d_puts(": ");
	d_print_d(divas_info->d_line_count, STDERR_FILENO);
	_diva_s_d_puts(": ");
	_diva_s_d_puts(divas_info->argv[0]);
	_diva_s_d_puts(": ");
	_diva_s_d_puts(fd_str);
}

/**
 * d_print_d - function prints a decimal (integer) number (d_base 10)
 * @input: the input
 * @d_fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int d_print_d(int d_input, int d_fd)
{
	int (*__d_putchar)(char) = _d_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (d_fd == STDERR_FILENO)
		__d_putchar = _diva_eputchar;
	if (d_input < 0)
	{
		_abs_ = -d_input;
		__d_putchar('-');
		count++;
	}
	else
		_abs_ = d_input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__d_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__d_putchar('0' + current);
	count++;

	return (count);
}

/**
 * d_convert_number - converter function, a clone of itoa
 * @num: number
 * @d_base: d_base
 * @d_flags: argument d_flags
 *
 * Return: d_string
 */
char *d_convert_number(long int num, int d_base, int d_flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *_d_ptr;
	unsigned long n = num;

	if (!(d_flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = d_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	_d_ptr = &buffer[49];
	*_d_ptr = '\0';

	do	{
		*--_d_ptr = array[n % d_base];
		n /= d_base;
	} while (n != 0);

	if (sign)
		*--_d_ptr = sign;
	return (_d_ptr);
}

/**
 * d_remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the d_string to modify
 *
 * Return: Always 0;
 */
void d_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
