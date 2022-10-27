/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:03:55 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/27 17:00:40 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static bool	check_multiple_n(char *string)
{
	int	i;

	if (string[0] != '-')
		return (false);
	else
		i = 1;
	while (string[i] && string[i] == 'n')
		i++;
	if (!string[i])
		return (true);
	else
		return (false);
}

static bool	set_no_nl(char *str)
{
	int	i;

	i = 1;
	if (bool_strcmp(str, "-n"))
		return (true);
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (i == 1)
			return (false);
		if (str[i] == '\0')
			return (true);
	}
	return (false);
}

static void	print_out_str(char *str)
{
	ft_putstr(str);
}

void	ft_echo(char **arg, struct s_minishell *minishell)
{
	int		i;
	bool	no_nl;

	i = 1;
	if (!arg[1])
	{
		write(1, "\n", 1);
		exit(0);
	}
	no_nl = set_no_nl(arg[1]);
	while (arg[i] && (bool_strcmp(arg[i], "-n") || check_multiple_n(arg[i])))
		i++;
	while (arg[i])
	{
		print_out_str(arg[i]);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_nl)
		newline();
	exit (0);
}
