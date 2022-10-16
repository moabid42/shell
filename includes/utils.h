/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:05:17 by moabid            #+#    #+#             */
/*   Updated: 2022/10/16 17:37:02 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "parser.h"
# include "execute.h"
# include "builtin.h"
# include "../src/utils/libft/libft.h"
# include "../src/utils/libft/reader.h"

# define SYNTAX_ERROR 	"[-] syntax error: format ./minishell"
# define MINI_INIT_ERROR "[-] error: Envirement variable error"
# define PARSE_ERROR		"[-] error: User input error"
# define UNEXPECTED_TOKEN "esh: syntax error near unexpected token `;;'"

# define NAME			"./minishell"
# define PROMPT			"esh"
# define PROMPT_TITLE	"PS1"

struct					s_scripts;
struct					s_token_stream;
struct					s_variable;
typedef struct s_env	t_env;

// char			*get_path(char *cmd, char **env); 
char					*get_path(char *cmd, t_env *env);

void					ft_error(char *str);
int						my_strcmp(const char *strg1, char *strg2);
void					*ft_malloc(size_t size);
unsigned int			ft_get_nb_strs(char const *s, char c);
void					printer(struct s_scripts *head);
void					free_split(char **strs);
struct s_scripts		*ft_create_stack_scripts(
							char **scripts_line, unsigned int count);
struct s_scripts		*ft_create_node_script(char *cmd);
void					printer_token(struct s_token_stream *scripts);
int						ft_isspace(int c);

char					**ft_split_tokens(struct s_scripts *script);
void					get_next_str(char **next_str,
							unsigned int *next_str_len);
unsigned int			get_nb_tokens(char const *s);
struct s_token_stream	*ft_create_stack_tkstream(
							struct s_minishell *minishell,
							char **tokens, unsigned int count);
void					garbage_collect_token(struct s_token_stream *lst);
bool					ft_isword(char *str);
char					*ft_special_trim(char *str, int c, int size);

bool					node_contain_special(char *str, int c);
bool					node_contain_special_single(char *str, int c);
/* FRANCISCO	*/
int						ignore_inside_special(char *string, char special);
char					*ft_cutter(char *string, int n_byte);
int						in_special( char c, char *special);
int						words_count(
							char *string, char split_char, char *special);
int						increase_i(
							char *string, char split_char, char *special);
bool					quotes_string_check(char **scripts_line, int num);
char					**ft_new_split(
							char *string, char split_char, char *special);
void					printer_split(char **tokens);

/*	 bool	ft_iscommand(char *str, char **env);	*/
bool					ft_iscommand(char *str, t_env *env);
bool					ft_isfile(char *str);
bool					ft_isword(char *str);
void					printer_variable(struct s_variable *variable);

void					print_the_env(t_env *enviroment);

#endif