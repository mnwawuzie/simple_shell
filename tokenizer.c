#include "shell.h"

/**
 * **d_strtow - splits a d_string into words. Repeat delimiters are ignored
 * @d_str: the input d_string
 * @d: the delimeter d_string
 * Return: a pointer to an array of d_strings, or NULL on failure
 */

char **d_strtow(char *d_str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (d_str == NULL || d_str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; d_str[i] != '\0'; i++)
		if (!is_diva_delimiter(d_str[i], d)
		&& (is_diva_delimiter(d_str[i + 1], d) || !d_str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_diva_delimiter(d_str[i], d))
			i++;
		k = 0;
		while (!is_diva_delimiter(d_str[i + k], d) && d_str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = d_str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **d_strtow2 - splits a d_string into words
 * @d_str: the input d_string
 * @d: the delimeter
 * Return: a pointer to an array of d_strings, or NULL on failure
 */
char **d_strtow2(char *d_str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (d_str == NULL || d_str[0] == 0)
		return (NULL);
	for (i = 0; d_str[i] != '\0'; i++)
		if ((d_str[i] != d && d_str[i + 1] == d) ||
		    (d_str[i] != d && !d_str[i + 1]) || d_str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (d_str[i] == d && d_str[i] != d)
			i++;
		k = 0;
		while (d_str[i + k] != d && d_str[i + k] && d_str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = d_str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
