#include "shell.h"

/**
 * _d_strcpy - copies a d_string
 * @d_dest_d_str: the d_dest_d_strination
 * @d_src_d_str: the source
 *
 * Return: pointer to d_dest_d_strination
 */
char *_d_strcpy(char *d_dest_d_str, char *d_src_d_str)
{
	int i = 0;

	if (d_dest_d_str == d_src_d_str || d_src_d_str == 0)
		return (d_dest_d_str);
	while (d_src_d_str[i])
	{
		d_dest_d_str[i] = d_src_d_str[i];
		i++;
	}
	d_dest_d_str[i] = 0;
	return (d_dest_d_str);
}

/**
 * _d_strdup - duplicates a d_string
 * @d_str: the d_string to duplicate
 *
 * Return: pointer to the duplicated d_string
 */
char *_d_strdup(const char *d_str)
{
	int length = 0;
	char *ret;

	if (d_str == NULL)
		return (NULL);
	while (*d_str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--d_str;
	return (ret);
}

/**
 *_d_puts - prints an input d_string
 *@d_str: the d_string to be printed
 *
 * Return: Nothing
 */
void _d_puts(char *d_str)
{
	int i = 0;

	if (!d_str)
		return;
	while (d_str[i] != '\0')
	{
		_d_putchar(d_str[i]);
		i++;
	}
}

/**
 * _d_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _d_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
