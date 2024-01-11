#include "shell.h"

/**
 * d_get_environ - returns the d_string array copy of our environ
 * @divas_info: d_structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **d_get_environ(info_t *divas_info)
{
	if (!divas_info->environ || divas_info->env_changed)
	{
		divas_info->environ = list_to_d_strings(divas_info->env);
		divas_info->env_changed = 0;
	}

	return (divas_info->environ);
}

/**
 * _d_und_setenv - Remove an environment variable
 * @divas_info: d_structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the d_string env var property
 */
int _d_und_setenv(info_t *divas_info, char *var)
{
	list_t *node = divas_info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = is_haystack_starts(node->d_str, var);
		if (p && *p == '=')
		{
			divas_info->env_changed = diva_del_node_at_index(&(divas_info->env), i);
			i = 0;
			node = divas_info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (divas_info->env_changed);
}

/**
 * _d_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @divas_info: d_structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the d_string env var property
 * @value: the d_string env var value
 *  Return: Always 0
 */
int _d_setenv(info_t *divas_info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_d_strlen(var) + _d_strlen(value) + 2);
	if (!buf)
		return (1);
	_d_strcpy(buf, var);
	_d_strcat(buf, "=");
	_d_strcat(buf, value);
	node = divas_info->env;
	while (node)
	{
		p = is_haystack_starts(node->d_str, var);
		if (p && *p == '=')
		{
			free(node->d_str);
			node->d_str = buf;
			divas_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	diva_addnode_end(&(divas_info->env), buf, 0);
	free(buf);
	divas_info->env_changed = 1;
	return (0);
}
