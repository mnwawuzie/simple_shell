#include "shell.h"

/**
 * d_is_d_cmd - This function determines if a file is an executable command
 * @divas_info: This is the divas_info d_struct
 * @d_path: This is the path to the file
 *
 * Return: 1 true, 0 false
 */
int d_is_d_cmd(info_t *divas_info, char *d_path)
{
	d_struct stat leo_st;

	(void)divas_info;
	if (!d_path || stat(d_path, &leo_st))
		return (0);

	if (leo_st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * now_dupl_chars - This function duplicates characters int his program
 * @d_pathd_str: This is the PATH d_string
 * @start: This represents the starting index
 * @stop: This argument reresents the stopping index
 *
 * Return: a pointer to new buffer
 */
char *now_dupl_chars(char *d_pathd_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (d_pathd_str[i] != ':')
			buf[k++] = d_pathd_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * d_find_path - this finds this cmd in the PATH d_string
 * @divas_info: this is an divas_info d_struct
 * @d_pathd_str: this is the PATH d_string
 * @cmd: represents the cmd to find
 *
 * Return: full path of the cmd, else NULL
 */
char *d_find_path(info_t *divas_info, char *d_pathd_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!d_pathd_str)
		return (NULL);
	if ((_d_strlen(cmd) > 2) && is_haystack_starts(cmd, "./"))
	{
		if (d_is_d_cmd(divas_info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!d_pathd_str[i] || d_pathd_str[i] == ':')
		{
			path = now_dupl_chars(d_pathd_str, curr_pos, i);
			if (!*path)
				_d_strcat(path, cmd);
			else
			{
				_d_strcat(path, "/");
				_d_strcat(path, cmd);
			}
			if (d_is_d_cmd(divas_info, path))
				return (path);
			if (!d_pathd_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
