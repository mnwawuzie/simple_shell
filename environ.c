#include "shell.h"

/**
 * divas_env - FUNCTION thst prints the current environment
 * @divas_info: a d_structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0 success
 */
int divas_env(info_t *divas_info)
{
	d_print_list_d_str(divas_info->env);
	return (0);
}

/**
 * divas_getenv - A function to get the value of an environ variable
 * @divas_info: This is the d_structure containing arguments. Used to maintain
 * @d_name: Represents the environmental variable name
 *
 * Return: the resulting value of the code
 */
char *divas_getenv(info_t *divas_info, const char *d_name)
{
	list_t *node = divas_info->env;
	char *d_p;

	while (node)
	{
		d_p = is_haystack_starts(node->d_str, d_name);
		if (d_p && *d_p)
			return (d_p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setdivaenv - This is a function to Initialize a new environment variable,
 *             or modify an existing one
 * @divas_info: The d_structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0
 */
int _setdivaenv(info_t *divas_info)
{
	if (divas_info->argc != 3)
	{
		_diva_s_d_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_d_setenv(divas_info, divas_info->argv[1], divas_info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetdivaenv - Remove an environment variable
 * @divas_info: d_structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _unsetdivaenv(info_t *divas_info)
{
	int d_i;

	if (divas_info->argc == 1)
	{
		_diva_s_d_puts("Too few arguements.\n");
		return (1);
	}
	for (d_i = 1; d_i <= divas_info->argc; d_i++)
		_d_und_setenv(divas_info, divas_info->argv[d_i]);

	return (0);
}

/**
 * diva_env_linkedlist_populate - populates env linked list
 * @divas_info: d_structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int diva_env_linkedlist_populate(info_t *divas_info)
{
	list_t *d_node = NULL;
	size_t d_n;

	for (d_n = 0; environ[d_n]; d_n++)
		diva_addnode_end(&d_node, environ[d_n], 0);
	divas_info->env = d_node;
	return (0);
}
