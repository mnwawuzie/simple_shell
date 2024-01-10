#include "shell.h"

/**
 * main - main function
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */

int main(void)
{
	char *input;
	char **tokens;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			input = get_line();
			if (input == NULL)
			{
				perror("can't read from stdin");
				exit(EXIT_FAILURE);
			}
			tokens = tokenization(input);
			execute_command(tokens);
			free_tokens(tokens);
			free(input);
		}

	}
	return (0);
}
