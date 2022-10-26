/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:08:52 by frame             #+#    #+#             */
/*   Updated: 2022/10/26 10:19:46 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int	error_exit(struct s_minishell *minishell,
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

bool	ft_iscommand(char *str, t_env *env)
{
	if (get_path(str, env))
		return (true);
	return (false);
}

bool	ft_isfile(char *str)
{
	if (access(str, F_OK))
		return (true);
	return (false);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
