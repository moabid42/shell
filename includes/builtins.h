/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:18:33 by moabid            #+#    #+#             */
/*   Updated: 2022/08/29 17:55:34 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"
#include "utils.h"
#include "execute.h"
#include "parser.h"
#include "../src/utils/libft/libft.h"

/*** UTILS ***/
void	newline();
void	ft_putstr(char *str);
/*** STRING_UTILS ***/
bool	string_value_cmp(char *str1, char *str2);
bool	check_string(char c, char *str);
int		find_chr(char *str, char c);
bool	bool_strcmp(char *str1, char *str2);
/*** LIST_UTILS ***/
/*** ENVIROMENT_SETTINGS ***/
char	*copy_till_bit(char *str, int n_byte);
char	**split_name_content(char *str);

/*** BUILDinS ***/
char	*get_pwd();
void	ft_env(t_env *env);
void	ft_echo(char **arg, struct minishell *minishell);
void	ft_export (int argc, char **argv, struct minishell *minishell);
void	ft_exit(char **argv, struct minishell *minishell);
void	ft_pwd(struct minishell *minishell);
void	ft_cd(char **argv, struct minishell *minishell);
char	**env_to_string(t_env *env);
/*** SORTING ***/

#endif