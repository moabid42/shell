/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:03:55 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/26 17:05:09 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// static bool check_dollar_sign(char* str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if(str[i] == '$')
// 			return true;
// 		i++;
// 	}
// 	return (false);
// }

// static char *string_dollar_sign(char *str)
// {
// 	int		i;
// 	char	*new_string;

// 	i = 0;
// 	while (str[i] != '$')
// 		i++;
// 	new_string = malloc(i + 1);
// 		if (!new_string)
// 			return (NULL);
// 	i = 0;
// 	while (str[i] != '$')
// 	{
// 		new_string[i] = str[i];
// 		i++;
// 	}
// 	new_string[i] = '\0';
// 	return (new_string);
// }

static bool check_multiple_n(char *string)
{
	int i;
	if(string[0] != '-')
		return false;
	else
		i = 1;
	while(string[i] && string[i] == 'n')
		i++;
	if(!string[i])
		return (true);
	else
		return (false);
}

static bool set_no_nl (char *str)
{
	if (bool_strcmp(str, "-n"))
		return (true);
	return (false);
}

static void print_out_str (char *str)
{
	// if (check_dollar_sign(str))
	// 	str = string_dollar_sign(str);
	ft_putstr_fd(str, 1);
}


int	ft_echo (char **arg, struct minishell *minishell)
{
	int		i;
	bool	no_nl;

	i = 1;
	
	if(!arg[1])
	{
		write(1, "\n", 1);
		exit(0);
	}
	no_nl = set_no_nl(arg[1]);
	while (arg[i] && (bool_strcmp(arg[i], "-n") || check_multiple_n(arg[i])))
		i++;
	while(arg[i])
	{
		print_out_str(arg[i]);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_nl)
		newline();
	exit(0);
}

// int main (int argc, char **argv)
// {
// 	if(!argv[1])
// 		return (0);
// 	ft_echo(&argv[0]);
// 	return(0);
// 	system("leak echo");
// }
