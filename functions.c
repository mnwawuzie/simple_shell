#include "shell.h"

/**
 * *_strcpy - copy the string pointed to by src
 * @src: copy to
 * @dest: destination
 * Return: 0;
 */
char *_strcpy(char *dest, char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	return (0);
}

/**
 * _strlen- returns length of string
 * @s: string
 * Return: Always 0.
 */
int _strlen(char *s)
{
	int a = 0;

	while (*s != '\0')
	{
		a++;
		s++;
	}
	return (a);
}

/**
 * _strcmp - a function to compare two strings
 * @s1: first string
 * @s2: second string
 * Return: 0.
 */
int _strcmp(char *s1, char *s2)
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


/**
 * _strdup - a function that duplicates a string
 * @str: the string to be duplicated
 *
 * Return: str
 */
char *_strdup(const char *str)
{
	int i, len = 0;
	char *duplicate;

	if (str == NULL)
	{
	return (NULL);
	}
	while (*str != '\0')
	{
		len++;
		str++;
	}
	duplicate = (char *)malloc(len + 1);
	if (duplicate == NULL)
	{
		return (NULL);
	}
	for (i = 0; i <= len; i++)
		duplicate[i] = str[i];

	return (duplicate);
}
