#include "shell.h"

/**
 * main - The main function entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 success, 1 error
 */

int main(int ac, char **av)
{
	info_t divas_info[] = { divas_info_INIT };
	int diva_d_d_fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (diva_d_d_fd)
		: "r" (diva_d_d_fd));

	if (ac == 2)
	{
		diva_d_d_fd = open(av[1], O_RDONLY);
		if (diva_d_d_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_diva_s_d_puts(av[0]);
				_diva_s_d_puts(": 0: Can't open ");
				_diva_s_d_puts(av[1]);
				_diva_eputchar('\n');
				_diva_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		divas_info->readd_fd = diva_d_d_fd;
	}
	diva_env_linkedlist_populate(divas_info);
	read_history_diva(divas_info);
	hsh(divas_info, av);
	return (EXIT_SUCCESS);
}
