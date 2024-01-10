#include "shell.h"

/**
 * free_tokens- a function that frees tokens
 * @tokens: tokens
 *
 * Return: 0
 */

void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
