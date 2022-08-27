/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:18:33 by moabid            #+#    #+#             */
/*   Updated: 2022/08/27 23:39:56 by moabid           ###   ########.fr       */
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
int		ft_env(int argc, char **argv, char **env);
int		ft_echo(char **arg, struct minishell *minishell);
int     ft_export (int argc, char **argv, struct minishell *minishell);
void    ft_exit(char **argv, struct minishell *minishell);
int     ft_pwd(struct minishell *minishell);
/*** SORTING ***/

#endif