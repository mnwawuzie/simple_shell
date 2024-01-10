#include "shell.h"

/**
 * execute_command - a function that executes commands
 * @command: command to be executed
 * @argv: argument vector
 * Return: 0
 */

int execute_command(char **command)
{
	pid_t pid;
	int status;
	char *envp[4];

	if (command[0] == NULL)
	{
		perror("Empty command");
			return (1);
	}
	envp[0] = "/bin/ls";
	envp[1] = "-l";
	envp[2] = "/usr/";
	envp[3] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(command[0], command, envp) == -1)
		{
			perror("Error:");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}
