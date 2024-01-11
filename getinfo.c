#include "shell.h"

/**
 * clear_divas_info - initializes info_t d_struct
 * @divas_info: d_struct address
 */
void clear_divas_info(info_t *divas_info)
{
	divas_info->arg = NULL;
	divas_info->argv = NULL;
	divas_info->path = NULL;
	divas_info->argc = 0;
}

/**
 * set_divas_info - initializes info_t d_struct
 * @divas_info: d_struct address
 * @av: argument vector
 */
void set_divas_info(info_t *divas_info, char **av)
{
	int i = 0;

	divas_info->fname = av[0];
	if (divas_info->arg)
	{
		divas_info->argv = d_strtow(divas_info->arg, " \t");
		if (!divas_info->argv)
		{

			divas_info->argv = malloc(sizeof(char *) * 2);
			if (divas_info->argv)
			{
				divas_info->argv[0] = _d_strdup(divas_info->arg);
				divas_info->argv[1] = NULL;
			}
		}
		for (i = 0; divas_info->argv && divas_info->argv[i]; i++)
			;
		divas_info->argc = i;

		diva_replace_d_alias(divas_info);
		diva_replace_d_vars(divas_info);
	}
}

/**
 * free_divas_info - frees info_t d_struct fields
 * @divas_info: d_struct address
 * @all: true if freeing all fields
 */
void free_divas_info(info_t *divas_info, int all)
{
	divs_ffree(divas_info->argv);
	divas_info->argv = NULL;
	divas_info->path = NULL;
	if (all)
	{
		if (!divas_info->cmd_buf)
			free(divas_info->arg);
		if (divas_info->env)
			d_free_d_list(&(divas_info->env));
		if (divas_info->history)
			d_free_d_list(&(divas_info->history));
		if (divas_info->alias)
			d_free_d_list(&(divas_info->alias));
		divs_ffree(divas_info->environ);
			divas_info->environ = NULL;
		d_be_free((void **)divas_info->cmd_buf);
		if (divas_info->readd_fd > 2)
			close(divas_info->readd_fd);
		_d_putchar(BUF_FLUSH);
	}
}
