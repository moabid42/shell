/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:05:17 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 19:05:58 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"
#include "parser.h"
#include "execute.h"
#include "builtin.h"
#include "../src/utils/libft/libft.h"
#include "../src/utils/libft/reader.h"

#define SYNTAX_ERROR 	"[-] syntax error: format ./minishell"
#define MINI_INIT_ERROR "[-] error: Envirement variable error"
#define PARSE_ERROR		"[-] error: User input error"
#define UNEXPECTED_TOKEN "esh: syntax error near unexpected token `;;'"
#define ENV_ERROR		"[-] error: Envirement variable not set"

#define NAME			"./minishell"
#define	PROMPT			"esh"
#define PROMPT_TITLE	"PS1"

struct scripts;
struct token_stream;
struct s_variable;
typedef struct s_env t_env;

char            *get_path(char *cmd, t_env *env);
void			ft_error(char *str);
int				my_strcmp(const char *strg1, char *strg2);
void			*ft_malloc(size_t size);
unsigned int	ft_get_nb_strs(char const *s, char c);
void			printer(struct scripts *head);
void			free_split(char **strs);
struct scripts	*ft_create_stack_scripts(char **scripts_line, unsigned int count);
struct scripts	*ft_create_node_script(char *cmd);
void			printer_token(struct token_stream *scripts);
int				ft_isspace(int c);


char				**ft_split_tokens(struct scripts *script);
void				get_next_str(char **next_str, unsigned int *next_str_len);
unsigned int		get_nb_tokens(char const *s);
struct token_stream	*ft_create_stack_tkstream(struct minishell *minishell, char **tokens, unsigned int count);

void				garbage_collect_token(struct token_stream *lst);
bool				ft_isword(char *str);
char				*ft_special_trim(char *str, int c, int size);

bool				node_contain_special(char *str, int c);
bool				node_contain_special_single(char *str, int c);


//////////////////////
//  MINISHELL_UTILS //
//////////////////////

char    *append_chr(char *str, char append);
char	*ft_free(void *ptr);
int     ft_strlen_newline(char *str);


//////////////////////
//  GENERAL_UTILS   //
//////////////////////

int     error_exit(struct minishell *minishell, char *str, char *var, int exit_code);

//////////////////////
//  PARSER_UTILS    //
//////////////////////

int     count_tokens(char **tokens);
void	print_tokens(char **scripts_line, int count);
void	printer_split(char **tokens);

//francisco shit
int		ignore_inside_special(char *string, char special);
char	*ft_cutter (char *string, int n_byte);
int		in_special( char c, char *special);
int		words_count(char *string, char split_char, char *special);
int		increase_i(char *string, char split_char, char *special);
bool	quotes_string_check(char **scripts_line, int num);
char	**ft_new_split(char *string, char split_char, char* special);
void	printer_split(char **tokens);

// bool	ft_iscommand(char *str, char **env);
bool	ft_iscommand(char *str, t_env *env);
bool	ft_isfile(char *str);
bool	ft_isword(char *str);
void	printer_variable(struct s_variable *variable);

void print_the_env(t_env *enviroment);


#endif