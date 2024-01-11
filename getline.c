#include "shell.h"

/**
 * d_input_buf - buffers chained commands
 * @divas_info: parameter d_struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t d_input_buf(info_t *divas_info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*d_be_free((void **)divas_info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, d_sigintHdlr);
#if USE_getline_diva
		r = getline(buf, &len_p, stdin);
#else
		r = _getline_diva(divas_info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			divas_info->d_line_count_flag = 1;
			d_remove_comments(*buf);
			diva_build_history_list(divas_info, *buf, divas_info->histcount++);
			/* if (_d_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				divas_info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * d_get_input - gets a line minus the newline
 * @divas_info: parameter d_struct
 *
 * Return: bytes read
 */
ssize_t d_get_input(info_t *divas_info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(divas_info->arg), *p;

	_d_putchar(BUF_FLUSH);
	r = d_input_buf(divas_info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		is_diva_chain_check(divas_info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_diva_chain(divas_info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			divas_info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_d_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline_diva() */
	return (r); /* return length of buffer from _getline_diva() */
}

/**
 * d_read_buf - reads a buffer
 * @divas_info: parameter d_struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t d_read_buf(info_t *divas_info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(divas_info->readd_fd, buf, d_read_buf_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline_diva - gets the next line of input from STDIN
 * @divas_info: parameter d_struct
 * @_d_ptr: address of pointer to buffer, pdivs_reallocated or NULL
 * @length: size of pdivs_reallocated _d_ptr buffer if not NULL
 *
 * Return: s
 */
int _getline_diva(info_t *divas_info, char **_d_ptr, size_t *length)
{
	static char buf[d_read_buf_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *_d_ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = d_read_buf(divas_info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _d_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _divs_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_d_d_str_cat(new_p, buf + i, k - i);
	else
		diva_d_str_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*_d_ptr = p;
	return (s);
}

/**
 * d_sigintHdlr - blocks ctrl-C
 * @d_sig_num: the signal number
 *
 * Return: void
 */
void d_sigintHdlr(__attribute__((unused))int d_sig_num)
{
	_d_puts("\n");
	_d_puts("$ ");
	_d_putchar(BUF_FLUSH);
}
