/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:34:20 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:20:11 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_variable	*variable_create(char **variable_list)
{
	struct s_variable	*variable;

	variable = ft_malloc(sizeof(struct s_variable));
	variable->var = variable_list[0];
	variable->value = variable_list[1];
	variable->next = NULL;
	return (variable);
}

void	variable_insert_node(struct s_variable *variable,
			struct s_variable *list)
{
	while (list)
	{
		if (!my_strcmp(list->var, variable->var))
		{
			list->value = variable->value;
			return ;
		}
		if (list->next)
			list = list->next;
		else
			break ;
	}
	list->next = variable;
}

bool	minishell_var_lookup(char *var_str, struct s_variable *variable)
{
	char	**var_list;

	var_list = ft_split(var_str, '=');
	while (variable)
	{
		if (!my_strcmp(variable->var, var_list[0])
			&& !my_strcmp(variable->value, var_list[1]))
		{
			free_split(var_list);
			return (true);
		}
		variable = variable->next;
	}
	free_split(var_list);
	return (false);
}

void	minishell_save_variable(char *variable_assigned,
		struct s_minishell *minishell)
{
	char				**variable_list;
	struct s_variable	*new;

	if (minishell_var_lookup(variable_assigned, minishell->variables) == true)
		return ;
	variable_list = ft_split(variable_assigned, '=');
	if (!minishell->variables)
		minishell->variables = variable_create(variable_list);
	else
	{
		new = variable_create(variable_list);
		variable_insert_node(new, minishell->variables);
	}
}

void	printer_variable(struct s_variable *variable)
{
	struct s_variable	*tmp;

	tmp = variable;
	while (tmp)
	{
		printf("We have %s = %s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}
