/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_prepar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:08:44 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:20:11 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	return (!my_strcmp(cmd, "export")
		|| !my_strcmp(cmd, "cd")
		|| !my_strcmp(cmd, "echo")
		|| !my_strcmp(cmd, "env")
		|| !my_strcmp(cmd, "pwd")
		|| !my_strcmp(cmd, "unset"));
}

void	builtin_run(char **cmd_list, struct s_minishell *minishell)
{
	if (!my_strcmp(cmd_list[0], "echo"))
		ft_echo(cmd_list, minishell);
	else if (!my_strcmp(cmd_list[0], "pwd"))
		ft_pwd(minishell);
	else if (!my_strcmp(cmd_list[0], "env"))
		ft_env(minishell->env);
}
