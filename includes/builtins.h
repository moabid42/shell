/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:18:33 by moabid            #+#    #+#             */
/*   Updated: 2022/09/08 12:06:21 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "minishell.h"
#include "utils.h"
#include "execute.h"
#include "parser.h"
#include "../src/utils/libft/libft.h"

typedef struct  s_env {
    char *name;
    char *content;
    struct s_env *next;
}               t_env;

/*** UTILS ***/
void	newline();
void	ft_putstr(char *str);

/*** STRING_UTILS ***/
bool	string_value_cmp(char *str1, char *str2);
bool	check_string(char c, char *str);
int		find_chr(char *str, char c);
bool	bool_strcmp(char *str1, char *str2);
/*** LIST_UTILS ***/
t_env	*new_node();
t_env	*create_node(t_env *env, char *name, char *content);
t_env	*fill_new_node(char *str, t_env *node);
t_env	*append_new_node(t_env *enviroment, t_env *node);
/*** ENVIROMENT_SETTINGS ***/
char	*copy_till_bit(char *str, int n_byte);
char	**split_name_content(char *str);
t_env	*create_the_env(char **env);
char    **env_to_string(t_env *env);
bool	is_a_valid_identifier(char *str);
/*** BUILDinS ***/
char	*get_pwd();
void    ft_env(t_env *enviroment);
void	ft_cd(char **argv, struct minishell *minishell);
void	ft_echo (char **arg, struct minishell *minishell);
void    ft_export (char **argv, struct minishell *minishell);
void    ft_exit(char **argv, struct minishell *minishell);
void	ft_pwd (struct minishell *minishell);
void    ft_unset(char **argv, struct minishell *minishell);
/*** SORTING ***/
t_env	*change_value(t_env *node);
t_env	*alphabetic_order(t_env *head);


#endif