/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:18:33 by moabid            #+#    #+#             */
/*   Updated: 2022/09/19 15:18:35 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "utils.h"
# include "execute.h"
# include "builtin_utils.h"
# include "parser.h"
# include "../src/utils/libft/libft.h"

void	ft_env(t_env *enviroment);
void	ft_cd(char **argv, struct s_minishell *minishell);
void	ft_echo(char **arg, struct s_minishell *minishell);
void	ft_export(char **argv, struct s_minishell *minishell);
void	ft_exit(char **argv, struct s_minishell *minishell);
void	ft_pwd(struct s_minishell *minishell);
void	ft_unset(char **argv, struct s_minishell *minishell);
void	cd_func(void);
int     ft_atoi_special(char *str);
bool	is_a_valid_identifier(char *str);

#endif