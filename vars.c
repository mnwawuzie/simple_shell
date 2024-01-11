#include "shell.h"

/**
 * is_diva_chain - test if current char in buffer is a chain delimeter
 * @divas_info: the parameter d_struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_diva_chain(info_t *divas_info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		divas_info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		divas_info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		divas_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * is_diva_chain_check - checks we should continue chaining d_based on last status
 * @divas_info: the parameter d_struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void is_diva_chain_check(info_t *divas_info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (divas_info->cmd_buf_type == CMD_AND)
	{
		if (divas_info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (divas_info->cmd_buf_type == CMD_OR)
	{
		if (!divas_info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * diva_replace_d_alias - replaces an aliases in the tokenized d_string
 * @divas_info: the parameter d_struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int diva_replace_d_alias(info_t *divas_info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = divas_node_is_haystack_starts(divas_info->alias, divas_info->argv[0], '=');
		if (!node)
			return (0);
		free(divas_info->argv[0]);
		p = _d_strchr(node->d_str, '=');
		if (!p)
			return (0);
		p = _d_strdup(p + 1);
		if (!p)
			return (0);
		divas_info->argv[0] = p;
	}
	return (1);
}

/**
 * diva_replace_d_vars - replaces vars in the tokenized d_string
 * @divas_info: the parameter d_struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int diva_replace_d_vars(info_t *divas_info)
{
	int i = 0;
	list_t *node;

	for (i = 0; divas_info->argv[i]; i++)
	{
		if (divas_info->argv[i][0] != '$' || !divas_info->argv[i][1])
			continue;

		if (!_d_strcmp(divas_info->argv[i], "$?"))
		{
			diva_replace_d_string(&(divas_info->argv[i]),
				_d_strdup(d_convert_number(divas_info->status, 10, 0)));
			continue;
		}
		if (!_d_strcmp(divas_info->argv[i], "$$"))
		{
			diva_replace_d_string(&(divas_info->argv[i]),
				_d_strdup(d_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = divas_node_is_haystack_starts(divas_info->env, &divas_info->argv[i][1], '=');
		if (node)
		{
			diva_replace_d_string(&(divas_info->argv[i]),
				_d_strdup(_d_strchr(node->d_str, '=') + 1));
			continue;
		}
		diva_replace_d_string(&divas_info->argv[i], _d_strdup(""));

	}
	return (0);
}

/**
 * diva_replace_d_string - replaces d_string
 * @old: address of old d_string
 * @new: new d_string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int diva_replace_d_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
