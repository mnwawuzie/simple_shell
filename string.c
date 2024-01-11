#include "shell.h"

/**
 * _d_strlen - THis function returns the length of a d_string
 * @leo_s: Represents the d_string whose length to check
 *
 * Return: length of d_string as integer
 */
int _d_strlen(char *leo_s)
{
	int d_i = 0;

	if (!leo_s)
		return (0);

	while (*leo_s++)
		d_i++;
	return (d_i);
}

/**
 * _d_strcmp - This function performs lexicogarphic comparison of two d_strangs.
 * @leo_s1: Represents the first d_strang
 * @leo_s2: Represents the second d_strang
 *
 * Return: s1 < s2 - negative, s1 > s2 - positive, s1 == s2 - zero
 */
int _d_strcmp(char *leo_s1, char *leo_s2)
{
	while (*leo_s1 && *leo_s2)
	{
		if (*leo_s1 != *leo_s2)
			return (*leo_s1 - *leo_s2);
		leo_s1++;
		leo_s2++;
	}
	if (*leo_s1 == *leo_s2)
		return (0);
	else
		return (*leo_s1 < *leo_s2 ? -1 : 1);
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
 * @leo_d_dest_d_str: represents the d_dest_d_strination buffer
 * @leo_d_src_d_str: represents the source buffer
 *
 * Return: a pointer to d_dest_d_strination buffer
 */
char *_d_strcat(char *leo_d_dest_d_str, char *leo_d_src_d_str)
{
	char *return_value = leo_d_dest_d_str;

	while (*leo_d_dest_d_str)
		leo_d_dest_d_str++;
	while (*leo_d_src_d_str)
		*leo_d_dest_d_str++ = *leo_d_src_d_str++;
	*leo_d_dest_d_str = *leo_d_src_d_str;
	return (return_value);
}
