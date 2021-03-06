/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:05:17 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 18:26:21 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"
#include "parser.h"
#include "../src/utils/libft/libft.h"

#define SYNTAX_ERROR 	"[-] syntax error: format ./minishell"
#define MINI_INIT_ERROR "[-] error: Envirement variable error"
#define PARSE_ERROR		"[-] error: User input error"
#define UNEXPECTED_TOKEN "esh: syntax error near unexpected token `;;'"

#define NAME			"./minishell"
#define	PROMPT			"esh"
#define PROMPT_TITLE	"PS1"

struct scripts;
struct token_stream;

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
struct token_stream	*ft_create_stack_tkstream(char **tokens, unsigned int count);

void				garbage_collect_token(struct token_stream *lst);
bool				ft_isword(char *str);

//francisco shit
int		ignore_inside_special(char *string, char special);
char	*ft_cutter (char *string, int n_byte);
int		in_special( char c, char *special);
int		words_count(char *string, char split_char, char *special);
int		increase_i(char *string, char split_char, char *special);
bool	quotes_string_check(char **scripts_line, int num);
char	**ft_new_split(char *string, char split_char, char* special);


#endif