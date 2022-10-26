/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:16:51 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 16:00:39 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "execute.h"
#include "parser.h"
#include "builtin_utils.h"

int	argv_length(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		++i;
	return (i);
}

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	are_all_numbers(char **argv, int length)
{
	int	i;

	i = 1;
	while (i < length)
	{
		if (ft_isnumber(argv[i]) == false)
			return (false);
		++i;
	}
	return (true);
}

void	exit_forward(char **argv)
{
	if (all_digits(argv[1]) == true && argv[1][0] != '\0')
		exit(ft_atoi_special(argv[1]));
	else
	{
		dprintf(2, "esh: exit: %s: "\
		"numeric argument required\n", argv[1]);
		free_split(argv);
		exit(255);
	}
}

void	ft_exit(char **argv, struct s_minishell *minishell)
{
	int			status;
	int			length;

	length = argv_length(argv);
	status = minishell->return_value;
	minishell_destroy(minishell);
	if (length > 2 && are_all_numbers(argv, length) == true)
	{
		write(2, "exit\n", 5);
		write(2, "esh: exit: too many arguments\n", 31);
		minishell->return_value = 1;
		return ;
	}
	if (minishell->type == SIMPLE)
		dprintf(2, "exit\n");
	if (argv[1])
		exit_forward(argv);
	else
	{
		free_split(argv);
		exit(status);
	}
}
