#include "shell.h"

/**
 * d_be_free - frees a pointer and NULLs the address
 * @_d_ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int d_be_free(void **_d_ptr)
{
	if (_d_ptr && *_d_ptr)
	{
		free(*_d_ptr);
		*_d_ptr = NULL;
		return (1);
	}
	return (0);
}
