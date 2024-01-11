#include "shell.h"

/**
 * diva_addnode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @d_str: d_str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *diva_addnode(list_t **head, const char *d_str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memset_b_d((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (d_str)
	{
		new_head->d_str = _d_strdup(d_str);
		if (!new_head->d_str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * diva_addnode_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @d_str: d_str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *diva_addnode_end(list_t **head, const char *d_str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memset_b_d((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (d_str)
	{
		new_node->d_str = _d_strdup(d_str);
		if (!new_node->d_str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * d_print_list_d_str - prints only the d_str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t d_print_list_d_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_d_puts(h->d_str ? h->d_str : "(nil)");
		_d_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * diva_del_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int diva_del_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->d_str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->d_str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * d_free_d_list - frees all nodes of a list
 * @head__d_ptr: address of pointer to head node
 *
 * Return: void
 */
void d_free_d_list(list_t **head__d_ptr)
{
	list_t *node, *next_node, *head;

	if (!head__d_ptr || !*head__d_ptr)
		return;
	head = *head__d_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->d_str);
		free(node);
		node = next_node;
	}
	*head__d_ptr = NULL;
}
