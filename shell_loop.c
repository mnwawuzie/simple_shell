#include "shell.h"

/**
 * hsh - main shell loop
 * @divas_info: the parameter & return divas_info d_struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *divas_info, char **av)
{
	ssize_t leo_r = 0;
	int builtin_ret = 0;

	while (leo_r != -1 && builtin_ret != -2)
	{
		clear_divas_info(divas_info);
		if (is_shell_interactive(divas_info))
			_d_puts("$ ");
		_diva_eputchar(BUF_FLUSH);
		leo_r = d_get_input(divas_info);
		if (leo_r != -1)
		{
			set_divas_info(divas_info, av);
			builtin_ret = d_find_builtin(divas_info);
			if (builtin_ret == -1)
				diva_find_cmd(divas_info);
		}
		else if (is_shell_interactive(divas_info))
			_d_putchar('\n');
		free_divas_info(divas_info, 0);
	}
	write_history_diva(divas_info);
	free_divas_info(divas_info, 1);
	if (!is_shell_interactive(divas_info) && divas_info->status)
		exit(divas_info->status);
	if (builtin_ret == -2)
	{
		if (divas_info->err_num == -1)
			exit(divas_info->status);
		exit(divas_info->err_num);
	}
	return (builtin_ret);
}
/**
 * d_find_builtin - finds a builtin command
 * @divas_info: the parameter & return divas_info d_struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int d_find_builtin(info_t *divas_info)
{
	int i, d_built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", divas_env},
		{"help", _myhelp},
		{"history", _diva_history},
		{"d_setenv", _setdivaenv},
		{"d_und_setenv", _unsetdivaenv},
		{"cd", _mycd},
		{"alias", _divas_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_d_strcmp(divas_info->argv[0], builtintbl[i].type) == 0)
		{
			divas_info->d_line_count++;
			d_built_in_ret = builtintbl[i].func(divas_info);
			break;
		}
	return (d_built_in_ret);
}

/**
 * diva_find_cmd - finds a command in PATH
 * @divas_info: the parameter & return divas_info d_struct
 *
 * Return: void
 */
void diva_find_cmd(info_t *divas_info)
{
	char *path = NULL;
	int i, k;

	divas_info->path = divas_info->argv[0];
	if (divas_info->d_line_count_flag == 1)
	{
		divas_info->d_line_count++;
		divas_info->d_line_count_flag = 0;
	}
	for (i = 0, k = 0; divas_info->arg[i]; i++)
		if (!is_delimiter(divas_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = d_find_path(divas_info, divas_getenv(divas_info, "PATH="), divas_info->argv[0]);
	if (path)
	{
		divas_info->path = path;
		diva_fork_cmd(divas_info);
	}
	else
	{
		if ((is_shell_interactive(divas_info) || divas_getenv(divas_info, "PATH=")
			|| divas_info->argv[0][0] == '/') && d_is_d_cmd(divas_info, divas_info->argv[0]))
			diva_fork_cmd(divas_info);
		else if (*(divas_info->arg) != '\n')
		{
			divas_info->status = 127;
			d_print_error(divas_info, "not found\n");
		}
	}
}

/**
 * diva_fork_cmd - forks a an exec thread to run cmd
 * @divas_info: the parameter & return divas_info d_struct
 *
 * Return: void
 */
void diva_fork_cmd(info_t *divas_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(divas_info->path, divas_info->argv, d_get_environ(divas_info)) == -1)
		{
			free_divas_info(divas_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(divas_info->status));
		if (WIFEXITED(divas_info->status))
		{
			divas_info->status = WEXITSTATUS(divas_info->status);
			if (divas_info->status == 126)
				d_print_error(divas_info, "Permission denied\n");
		}
	}
}
