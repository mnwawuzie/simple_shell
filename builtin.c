#include "shell.h"

/**
 * _diva_myexit - This defines a function that would exit the shell
 * @diva_divas_info: this Represents the d_struct containing arguments
 *      that is used to maintain the constant function prototype.
 *  Return: exits with exit status (0)
 *          if divas_info.argv[0] != "exit"
 */
int _diva_myexit(info_t *diva_divas_info)
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
			return (98);
		}
		diva_divas_info->err_num = _d_erratoi(diva_divas_info->argv[1]);
		return (-2);
	}
	diva_divas_info->err_num = -1;
	return (-2);
}

/**
 * _diva_mycd - this function changes the current directory of the process
 * @diva_divas_info: this represents the d_structure containing potential
 *         arguments that is used to maintain constant function prototype.
 *  Return: Always 0
 */
int _diva_mycd(info_t *diva_divas_info)
{
	char *d_s, *d_dir, buffer[1024];
	int d_chdir_ret;

	d_s = getcwd(buffer, 1024);
	if (!d_s)
		_d_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!diva_divas_info->argv[1])
	{
		d_dir = divas_getenv(diva_divas_info, "HOME=");
		if (!d_dir)
			d_chdir_ret = /* TODO: what should this be? */
				chdir((d_dir = divas_getenv(diva_divas_info, "PWD=")) ? d_dir : "/");
		else
			d_chdir_ret = chdir(d_dir);
	}
	else if (_d_strcmp(diva_divas_info->argv[1], "-") == 0)
	{
		if (!divas_getenv(diva_divas_info, "OLDPWD="))
		{
			_d_puts(d_s);
			_d_putchar('\n');
			return (1);
		}
		_d_puts(divas_getenv(diva_divas_info, "OLDPWD=")), _d_putchar('\n');
		d_chdir_ret = /* TODO: what should this be? */
			chdir((d_dir = divas_getenv(diva_divas_info, "OLDPWD=")) ? d_dir : "/");
	}
	else
		d_chdir_ret = chdir(diva_divas_info->argv[1]);
	if (d_chdir_ret == -1)
	{
		d_print_error(diva_divas_info, "can't cd to ");
		_diva_s_d_puts(diva_divas_info->argv[1]), _diva_eputchar('\n');
	}
	else
	{
		_d_setenv(diva_divas_info, "OLDPWD", divas_getenv(diva_divas_info, "PWD="));
		_d_setenv(diva_divas_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _diva_myhelp - THis function changes the current directory of the process
 * @diva_divas_info: Represents the d_structure containing arguments.
 *  Used to maintain constant function prototype.
 *  Return: 0
 */
int _diva_myhelp(info_t *diva_divas_info)
{
	char **d_arg_array;

	d_arg_array = diva_divas_info->argv;
	_d_puts("help call works. Function not yet implemented \n");
	if (0)
		_d_puts(*d_arg_array); /* temp att_unused workaround */
	return (0);
}
