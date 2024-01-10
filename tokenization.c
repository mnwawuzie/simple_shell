#include "shell.h"

/**
 * tokenization - a function that parses user input
 * @input: user inputs
 *
 * Return: tokens
 */

char **tokenization(char *input)
{
	int i = 0;
	char **tokens;
	char *token;

	tokens = (char **)malloc(sizeof(char *) * MAX_TOKENS);
	if (tokens == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, " \t\n");

	while (token != NULL && i < MAX_TOKENS - 1)
	{
		tokens[i++] = _strdup(token);
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}
