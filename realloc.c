#include "shell.h"

/**
 **memset_b_d - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *memset_b_d(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * divs_ffree - frees a d_string of d_strings
 * @pp: d_string of d_strings
 */
void divs_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _divs_realloc - divs_reallocates a block of memory
 * @_d_ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_divs_realloc(void *_d_ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!_d_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(_d_ptr), NULL);
	if (new_size == old_size)
		return (_d_ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)_d_ptr)[old_size];
	free(_d_ptr);
	return (p);
}
