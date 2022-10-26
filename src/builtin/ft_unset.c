/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:21:03 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/26 09:25:02 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static t_env	*remove_env_var(t_env *enviroment, t_env *node_to_erase)
{
	t_env	*tmp;

	tmp = enviroment;
	if (tmp && tmp == node_to_erase)
	{
		tmp = tmp->next;
		free(node_to_erase);
	}
	else
	{
		while (tmp && tmp->next && tmp->next != node_to_erase)
			tmp = tmp->next;
	}
	if (tmp->next == node_to_erase)
	{
		tmp->next = (tmp->next)->next;
		free(node_to_erase);
	}
	return (enviroment);
}

bool	is_valid(char *str)
{
	int		i;
	int		j;
	char	*invalid_char;

	invalid_char = (char *) "#@&*}${!?-+";
	i = 0;
	if (str[0] == '=' || str[0] == '\0')
		return (false);
	while (str[i])
	{
		j = 0;
		while (invalid_char[j] && invalid_char[j] != str[i])
			j++;
		if (invalid_char[j])
			return (false);
		i++;
	}
	if (ft_isdigit(str[0]))
		return (false);
	else
		return (true);
}

void	ft_unset(char **argv, struct s_minishell *minishell)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = minishell->env;
	if (!argv[1])
		;
	else
	{
		while (argv[i])
		{
			tmp = minishell->env;
			if (is_valid(argv[i]))
			{
				while (tmp)
				{
					if (my_strcmp(tmp->name, argv[i]) == 0)
					{
						minishell->env = remove_env_var(minishell->env, tmp);
						break ;
					}
					tmp = tmp->next;
				}
			}
			else
			{
				dprintf(2, "esh: unset: `%s': not a valid identifier\n",
					argv[i]);
				minishell->return_value = 1;
			}
			i++;
		}
	}
}
