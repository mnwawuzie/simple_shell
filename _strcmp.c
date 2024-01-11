#include "shell.h"

/**
 * _d_strcmp - a function to compare two d_strings
 * @s1: first d_string
 * @s2: second d_string
 * Return: 0.
 */
int _d_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
