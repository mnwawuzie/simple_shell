#include "shell.h"

/**
 * d_list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t d_list_len(const list_t *d_h)
{
	size_t i = 0;

	while (d_h)
	{
		d_h = d_h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_d_strings - returns an array of d_strings of the list->d_str
 * @head: pointer to first node
 *
 * Return: array of d_strings
 */
char **list_to_d_strings(list_t *head)
{
	list_t *node = head;
	size_t i = d_list_len(head), j;
	char **d_strs;
	char *d_str;

	if (!head || !i)
		return (NULL);
	d_strs = malloc(sizeof(char *) * (i + 1));
	if (!d_strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		d_str = malloc(_d_strlen(node->d_str) + 1);
		if (!d_str)
		{
			for (j = 0; j < i; j++)
				free(d_strs[j]);
			free(d_strs);
			return (NULL);
		}

		d_str = _d_strcpy(d_str, node->d_str);
		d_strs[i] = d_str;
	}
	d_strs[i] = NULL;
	return (d_strs);
}


/**
 * d_print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t d_print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_d_puts(d_convert_number(h->num, 10, 0));
		_d_putchar(':');
		_d_putchar(' ');
		_d_puts(h->d_str ? h->d_str : "(nil)");
		_d_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * divas_node_is_haystack_starts - returns node whose d_string starts with divas_prefix
 * @node: pointer to list head
 * @divas_prefix: d_stringd_list_len to match
 * @c: the next character after divas_prefix to match
 *
 * Return: match node or null
 */
list_t *divas_node_is_haystack_starts(list_t *node, char *divas_prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = is_haystack_starts(node->d_str, divas_prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index_diva - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index_diva(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
