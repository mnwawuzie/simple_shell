#include "shell.h"

/**
 **diva_d_str_cpy - copies a d_string
 *@d_dest_d_str: the d_dest_d_strination d_string to be copied to
 *@d_src_d_str: the source d_string
 *@n: the amount of characters to be copied
 *Return: the concatenated d_string
 */
char *diva_d_str_cpy(char *d_dest_d_str, char *d_src_d_str, int n)
{
	int i, j;
	char *s = d_dest_d_str;

	i = 0;
	while (d_src_d_str[i] != '\0' && i < n - 1)
	{
		d_dest_d_str[i] = d_src_d_str[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d_dest_d_str[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_d_d_str_cat - concatenates two d_strings
 *@d_dest_d_str: the first d_string
 *@d_src_d_str: the second d_string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated d_string
 */
char *_d_d_str_cat(char *d_dest_d_str, char *d_src_d_str, int n)
{
	int i, j;
	char *s = d_dest_d_str;

	i = 0;
	j = 0;
	while (d_dest_d_str[i] != '\0')
		i++;
	while (d_src_d_str[j] != '\0' && j < n)
	{
		d_dest_d_str[i] = d_src_d_str[j];
		i++;
		j++;
	}
	if (j < n)
		d_dest_d_str[i] = '\0';
	return (s);
}

/**
 **_d_strchr - locates a character in a d_string
 *@s: the d_string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_d_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
