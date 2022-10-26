/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:59:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 10:12:28 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	minishell_error(struct s_minishell *minishell, char *str)
{
	minishell->return_value = 1;
}

unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	if (nb_strs == 0)
		return (1);
	return (nb_strs);
}

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
