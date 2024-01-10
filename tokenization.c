#include "shell.h"

/**
 * tokenization - a function that parses user input
 * @input: user inputs
 * @tokens: tokens
 *
 * Return: tokens
 */

void tokenization(char *input, char *tokens[])
{
	int i = 0;
	char *token = strtok(input, " \t\n");

	while (token != NULL)
	{
		tokens[i++] = _strdup(token);
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
}
