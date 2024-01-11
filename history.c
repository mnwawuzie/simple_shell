#include "shell.h"

/**
 * d_get_history_file - gets the history file
 * @divas_info: parameter d_struct
 *
 * Return: allocated d_string containg history file
 */

char *d_get_history_file(info_t *divas_info)
{
	char *buf, *dir;

	dir = divas_getenv(divas_info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_d_strlen(dir) + _d_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_d_strcpy(buf, dir);
	_d_strcat(buf, "/");
	_d_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history_diva - creates a file, or appends to an existing file
 * @divas_info: the parameter d_struct
 *
 * Return: 1 on success, else -1
 */
int write_history_diva(info_t *divas_info)
{
	ssize_t d_fd;
	char *filename = d_get_history_file(divas_info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	d_fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (d_fd == -1)
		return (-1);
	for (node = divas_info->history; node; node = node->next)
	{
		_d_d_putsd_fd(node->d_str, d_fd);
		_d_putd_fd('\n', d_fd);
	}
	_d_putd_fd(BUF_FLUSH, d_fd);
	close(d_fd);
	return (1);
}

/**
 * read_history_diva - reads history from file
 * @divas_info: the parameter d_struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history_diva(info_t *divas_info)
{
	int i, last = 0, d_line_count = 0;
	ssize_t d_fd, rdlen, fsize = 0;
	d_struct stat st;
	char *buf = NULL, *filename = d_get_history_file(divas_info);

	if (!filename)
		return (0);

	d_fd = open(filename, O_RDONLY);
	free(filename);
	if (d_fd == -1)
		return (0);
	if (!fstat(d_fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(d_fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(d_fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			diva_build_history_list(divas_info, buf + last, d_line_count++);
			last = i + 1;
		}
	if (last != i)
		diva_build_history_list(divas_info, buf + last, d_line_count++);
	free(buf);
	divas_info->histcount = d_line_count;
	while (divas_info->histcount-- >= HIST_MAX)
		diva_del_node_at_index(&(divas_info->history), 0);
	diva_renumber_history(divas_info);
	return (divas_info->histcount);
}

/**
 * diva_build_history_list - adds entry to a history linked list
 * @divas_info: d_structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @d_line_count: the history d_line_count, histcount
 *
 * Return: Always 0
 */
int diva_build_history_list(info_t *divas_info, char *buf, int d_line_count)
{
	list_t *node = NULL;

	if (divas_info->history)
		node = divas_info->history;
	diva_addnode_end(&node, buf, d_line_count);

	if (!divas_info->history)
		divas_info->history = node;
	return (0);
}

/**
 * diva_renumber_history - renumbers the history linked list after changes
 * @divas_info: d_structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int diva_renumber_history(info_t *divas_info)
{
	list_t *node = divas_info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (divas_info->histcount = i);
}
