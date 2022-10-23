/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:00:58 by moabid            #+#    #+#             */
/*   Updated: 2022/09/19 19:02:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_UTILS_H
#define BUILTIN_UTILS_H

#include "minishell.h"
#include "utils.h"
#include "execute.h"
#include "parser.h"
#include "builtin.h"
#include "../src/utils/libft/libft.h"

struct minishell;

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
/*** SORTING ***/
t_env	*change_value(t_env *node);
t_env	*alphabetic_order(t_env *head);


#endif