#include "shell.h"

/**
 * _d_strlen - THis function returns the length of a d_string
 * @diva_d_s: Represents the d_string whose length to check
 *
 * Return: length of d_string as integer
 */
int _d_strlen(char *diva_d_s)
{
	int d_i = 0;

	if (!diva_d_s)
		return (0);

	while (*diva_d_s++)
		d_i++;
	return (d_i);
}

/**
 * _d_strcmp - This function performs lexicogarphic
 *  comparison of two d_strangs.
 * @diva_d_s1: Represents the first d_strang
 * @diva_d_s2: Represents the second d_strang
 *
 * Return: s1 < s2 - negative, s1 > s2 - positive, s1 == s2 - zero
 */
int _d_strcmp(char *diva_d_s1, char *diva_d_s2)
{
	while (*diva_d_s1 && *diva_d_s2)
	{
		if (*diva_d_s1 != *diva_d_s2)
			return (*diva_d_s1 - *diva_d_s2);
		diva_d_s1++;
		diva_d_s2++;
	}
	if (*diva_d_s1 == *diva_d_s2)
		return (0);
	else
		return (*diva_d_s1 < *diva_d_s2 ? -1 : 1);
}

/**
 * is_haystack_starts - This function checks if needle starts with haystack
 * @diva_haystack: Represents d_string to search
 * @d_needle: Represents the subd_string to find
 *
 * Return: address of next char of haystack or NULL
 */
char *is_haystack_starts(const char *diva_haystack, const char *d_needle)
{
	while (*d_needle)
		if (*d_needle++ != *diva_haystack++)
			return (NULL);
	return ((char *)diva_haystack);
}

/**
 * _d_strcat - This function concatenates two d_strings
 * @diva_d_d_dest_d_str: represents the d_dest_d_strination buffer
 * @diva_d_d_src_d_str: represents the source buffer
 *
 * Return: a pointer to d_dest_d_strination buffer
 */
char *_d_strcat(char *diva_d_d_dest_d_str, char *diva_d_d_src_d_str)
{
	char *return_value = diva_d_d_dest_d_str;

	while (*diva_d_d_dest_d_str)
		diva_d_d_dest_d_str++;
	while (*diva_d_d_src_d_str)
		*diva_d_d_dest_d_str++ = *diva_d_d_src_d_str++;
	*diva_d_d_dest_d_str = *diva_d_d_src_d_str;
	return (return_value);
}
