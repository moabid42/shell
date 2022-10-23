/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:37:08 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 21:50:44 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int isdir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);
    return S_ISREG(path.st_mode);
}

char	*find_return_expend(struct minishell *minishell, char return_var)
{
	if (return_var == '?')
		return (ft_itoa(minishell->return_value));
	return (NULL);
}

char	*minishell_find_variable(struct minishell *minishell, char *variable)
{
	struct s_variable	*iterator;
	t_env				*tmp;
	int					i;

	iterator = minishell->variables;
	tmp = minishell->env;
	i = 0;
	while (iterator)
	{
		if (my_strcmp(iterator->var, variable + 1) == 0)
			return (iterator->value);
		iterator = iterator->next;
	}
	while (tmp)
	{
		if (!my_strcmp(tmp->name, variable + 1))
			return (tmp->content);
		tmp = tmp->next;
	}
	if (variable[1] == '?')
		return (find_return_expend(minishell, '?'));
	return (NULL);
}

