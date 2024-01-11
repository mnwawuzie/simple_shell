#include "shell.h"

/**
 *_diva_s_d_puts - prints an input d_string
 * @this_diva_d_str: Represents d_string to be printed
 *
 * Return: Nothing
 */
void _diva_s_d_puts(char *this_diva_d_str)
{
	int d_i = 0;

	if (!this_diva_d_str)
		return;
	while (this_diva_d_str[d_i] != '\0')
	{
		_diva_eputchar(this_diva_d_str[d_i]);
		d_i = d_i + 1;
	}
}

/**
 * _diva_eputchar - writes the character c to stderr
 * @diva_char: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _diva_eputchar(char diva_char)
{
	static int d_i;
	static char diva_buf[WRITE_BUF_SIZE];

	if (diva_char == BUF_FLUSH || d_i >= WRITE_BUF_SIZE)
	{
		write(2, diva_buf, d_i);
		d_i = 0;
	}
	if (diva_char != BUF_FLUSH)
		diva_buf[d_i = d_i + 1] = diva_char;
	return (1);
}
