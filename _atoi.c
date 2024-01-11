#include "shell.h"

/**
 * diva_shell_interactive - function that returns true if the shell,
 * is in interactive mode
 * @diva_divas_info: this is the d_struct address
 *
 * Return: 1 if it's on interactive mode, 0 if otherwise
 */
int diva_shell_interactive(info_t *diva_divas_info)
{
	return (isatty(STDIN_FILENO) && diva_divas_info->readd_fd <= 2);
}

/**
 * is_diva_delimiter - a function that checks if character is a delimiter
 * @diva_c: this is the char to check
 * @diva_delim: this is the delimiter d_string
 * Return: 1 if true, 0 if false
 */
int is_diva_delimiter(char diva_c, char *diva_delim)
{
	while (*diva_delim)
		if (*diva_delim++ == diva_c)
			return (1);
	return (0);
}

/**
 * diva_alpha -function to check for alphabetic character
 * @diva_c: this is the character to input
 * Return: 1 if cthe character diva_c is alphabetic, 0 if otherwise
 */

int diva_alpha(int diva_c)
{
	if ((diva_c >= 'a' && diva_c <= 'z') || (diva_c >= 'A' && diva_c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * diva_d_str_to_int - function that converts a d_string to an integer
 * @diva_d_str: this is the d_string to be converted
 * Return: 0 if no numbers in d_string, converted number otherwise
 */

int diva_d_str_to_int(char *diva_d_str)
{
	int diva_i, diva_sign = 1, diva_flag = 0, diva_result = 0;

	for (diva_i = 0; diva_d_str[diva_i] != '\0' && diva_flag != 2; diva_i++)
	{
		if (diva_d_str[diva_i] == '-')
			diva_sign *= -1;

		if (diva_d_str[diva_i] >= '0' && diva_d_str[diva_i] <= '9')
		{
			diva_flag = 1;
			diva_result *= 10;
			diva_result += (diva_d_str[diva_i] - '0');
		}
		else if (diva_flag == 1)
			diva_flag = 2;
	}

	if (diva_sign == -1)
		return (-diva_result);
	else
		return (diva_result);
}
