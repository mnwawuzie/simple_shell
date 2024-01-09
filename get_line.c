#include "shell.h"
/**
 * get_line - a function to get line from a user
 *
 * Return: input from user
 */

char *get_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n;

	write(1, "$ ", 2);
	n = getline(&line, &len, stdin);
	if (n == -1)
	{
		perror("can't read from stdin");
		free(line);
		exit(EXIT_FAILURE);
	}
	if (line[n - 1] == '\n')
	{
		line[n - 1] = '\0';
	}
	return (line);
}
