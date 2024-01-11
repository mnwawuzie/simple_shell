#include "shell.h"

/**
 * _diva_history - This function displays the history list, one command by line,
 *	preceded with line numbers, starting at 0.
 * @divas_info: represents d_structure containing arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _diva_history(info_t *divas_info)
{
	d_print_list(divas_info->history);
	return (0);
}

/**
 * diva_undiva_set_alias - This function sets alias to d_string
 * @divas_info: parameter d_struct
 * @this_diva_d_str: the d_string alias
 *
 * Return: Success 0, error 1
 */
int diva_undiva_set_alias(info_t *divas_info, char *this_diva_d_str)
{
	char *d_p, leo_c;
	int leo_ret;

	d_p = _d_strchr(this_diva_d_str, '=');
	if (!d_p)
		return (1);
	leo_c = *d_p;
	*d_p = 0;
	leo_ret = diva_del_node_at_index(&(divas_info->alias),
		get_node_index_diva(divas_info->alias,
			divas_node_is_haystack_starts(divas_info->alias, this_diva_d_str, -1)));
	*d_p = leo_c;
	return (leo_ret);
}

/**
 * diva_set_alias - THis function sets alias to d_string
 * @divas_info: Represents parameter d_struct
 * @this_diva_d_str: represents the d_string alias
 *
 * Return: Success 0, error 1
 */
int diva_set_alias(info_t *divas_info, char *this_diva_d_str)
{
	char *d_p;

	d_p = _d_strchr(this_diva_d_str, '=');
	if (!d_p)
		return (1);
	if (!*++d_p)
		return (diva_undiva_set_alias(divas_info, this_diva_d_str));

	diva_undiva_set_alias(divas_info, this_diva_d_str);
	return (diva_addnode_end(&(divas_info->alias), this_diva_d_str, 0) == NULL);
}

/**
 * diva_print_alias - this function prints an alias d_string
 * @node: represents the alias node
 *
 * Return: Success 0, error 1
 */
int diva_print_alias(list_t *node)
{
	char *d_p = NULL, *leo_a = NULL;

	if (node)
	{
		d_p = _d_strchr(node->d_str, '=');
		for (leo_a = node->d_str; leo_a <= d_p; leo_a++)
			_d_putchar(*leo_a);
		_d_putchar('\'');
		_d_puts(d_p + 1);
		_d_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _divas_alias - this function mimics the alias builtin (man alias)
 * @divas_info: Represents d_structure containing arguments. Used to maintain
 *          constant function prototype.
 *  Return: 0
 */
int _divas_alias(info_t *divas_info)
{
	int d_i = 0;
	char *d_p = NULL;
	list_t *node = NULL;

	if (divas_info->argc == 1)
	{
		node = divas_info->alias;
		while (node)
		{
			diva_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (d_i = 1; divas_info->argv[d_i]; d_i++)
	{
		d_p = _d_strchr(divas_info->argv[d_i], '=');
		if (d_p)
			diva_set_alias(divas_info, divas_info->argv[d_i]);
		else
			diva_print_alias(divas_node_is_haystack_starts(divas_info->alias, divas_info->argv[d_i], '='));
	}

	return (0);
}
