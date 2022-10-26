/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:46:34 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 12:57:44 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	node_contain_special_single(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] == ' ')
			return (true);
		i++;
	}
	return (false);
}

bool	node_contain_special(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		if (count == 2)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_special_trim(char *str, int c, int size)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_malloc(sizeof(char) * (size - i));
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[ft_strlen(new)] = '\0';
	return (new);
}

int	error_exit(struct s_minishell *minishell, char *str,
					char *var, int exit_code)
{
	if (var == NULL)
		write(2, str, ft_strlen(str));
	else
	{
		write(2, str, ft_strlen(str));
		write(2, var, ft_strlen(var));
		write(2, "\'\n", 2);
	}
	minishell->return_value = exit_code;
	return (true);
}

struct s_ast	*error_exit_null(struct s_minishell *minishell,
				char *str, char *var, int exit_code)
{
	if (var == NULL)
		write(2, str, ft_strlen(str));
	else
	{
		write(2, str, ft_strlen(str));
		write(2, var, ft_strlen(var));
		write(2, "\'\n", 2);
	}
	minishell->return_value = exit_code;
	return (NULL);
}
