#include "shell.h"

/**
 * diva_myexit - This defines a function that would exit the shell
 * @diva_divas_info: this Represents the d_struct containing arguments that is used to maintain the
 *          constant function prototype.
 *  Return: exits with exit status (0)
 *  		if divas_info.argv[0] != "exit"
 */
int diva_myexit(info_t *diva_divas_info)
{
	int diva_exitcheck;

	if (diva_divas_info->argv[1])  /* If exit argument is present */
	{
		diva_exitcheck = _d_erratoi(diva_divas_info->argv[1]);
		if (diva_exitcheck == -1)
		{
			diva_divas_info->status = 2;
			d_print_error(diva_divas_info, "Illegal number: ");
			_diva_s_d_puts(diva_divas_info->argv[1]);
			_diva_eputchar('\n');
			return (1);
		}
		diva_divas_info->err_num = _d_erratoi(diva_divas_info->argv[1]);
		return (-2);
	}
	diva_divas_info->err_num = -1;
	return (-2);
}