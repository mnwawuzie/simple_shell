#include "shell.h"

/**
 * _d_putd_fd - writes the character c to given d_fd
 * @c: The character to print
 * @d_fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _d_putd_fd(char c, int d_fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(d_fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_d_d_putsd_fd - prints an input d_string
 * @d_str: the d_string to be printed
 * @d_fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _d_d_putsd_fd(char *d_str, int d_fd)
{
	int i = 0;

	if (!d_str)
		return (0);
	while (*d_str)
	{
		i += _d_putd_fd(*d_str++, d_fd);
	}
	return (i);
}
