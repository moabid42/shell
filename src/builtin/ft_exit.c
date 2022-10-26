/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:16:51 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:20:14 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "utils.h"
#include "execute.h"
#include "parser.h"
#include "builtin_utils.h"

bool	all_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			&& str[i] != '-'
			&& str[i] != '+')
			return (false);
		++i;
	}
	return (true);
}

int	argv_length(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		++i;
	return (i);
}

unsigned long long	ft_atoi_big(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (!my_strcmp(str, "9223372036854775808"))
		return (255);
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	if ((num * sign) == (MIN_SIZE - 1))
		return(-42);
	else if ((num * sign) == (MAX_SIZE + 1))
		return(42);
	if (((num * sign) >= MAX_SIZE || (num * sign) <= MIN_SIZE))
		return (0);
	return (num * sign);
}

int	ft_atoi_special(char *str)
{
	long long	num;

	num = ft_atoi_big(str);
	if (num < 0)
	{
		if (num == -42 && ft_strlen(str) > 3)
			return (0);
		return (num + 256);
	}
	else
	{
		if (num == 42 && ft_strlen(str) > 2)
			return (255);
		else if (num == 0 && ft_strlen(str) > 1)
			return (255);
		return (num % 256);
	}
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
	else
	{
		free_split(argv);
		exit(status);
	}
}
