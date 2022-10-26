/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:05:17 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 09:36:42 by frame            ###   ########.fr       */
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
# define ENV_ERROR		"[-] error: Envirement variable not set"

# define ERROR_B 		"esh: syntax error near unexpected token ')'\n"

# define NAME			"./minishell"
# define PROMPT		    "esh"
# define PROMPT_TITLE	"PS1"

struct					s_scripts;
struct					s_token_stream;
struct					s_variable;
struct					s_minishell;
typedef struct s_env	t_env;

struct s_data
{
	int		i;
	int		j;
	bool	open;
	char	q_type;
	char	*ret_str;
	char	*str;
};

char					*get_path(char *cmd, t_env *env);
void					ft_error(char *str);
int						my_strcmp(const char *strg1, char *strg2);
void					*ft_malloc(size_t size);
unsigned int			ft_get_nb_strs(char const *s, char c);
void					printer(struct s_scripts *head);
void					free_split(char **strs);
struct s_scripts		*ft_create_stack_scripts(char **scripts_line,
							unsigned int count);
struct s_scripts		*ft_create_node_script(char *cmd);
void					printer_token(struct s_token_stream *scripts);
int						ft_isspace(int c);

char					**ft_split_tokens(struct s_scripts *script);
void					get_next_str(char **next_str,
							unsigned int *next_str_len);
unsigned int			get_nb_tokens(char const *s);
struct s_token_stream	*stack_create(struct s_minishell *minishell,
							char **tokens, unsigned int count);

void					garbage_collect_token(struct s_token_stream *lst);
bool					ft_isword(char *str);
char					*ft_special_trim(char *str, int c, int size);

bool					node_contain_special(char *str, int c);
bool					node_contain_special_single(char *str, int c);
struct s_ast			*error_exit_null(struct s_minishell *minishell,
							char *str, char *var, int exit_code);
char					*parser(char *cmd, char *paths);
//////////////////////
//  MINISHELL_UTILS //
//////////////////////

char					*append_chr(char *str, char append);
char					*ft_free(void *ptr);
int						ft_strlen_newline(char *str);
bool					is_weirdo(char *input_line,
							struct s_minishell *minishell);

//////////////////////
//  GENERAL_UTILS   //
//////////////////////

int						error_exit(struct s_minishell *minishell, char *str,
							char *var, int exit_code);

//////////////////////
//  PARSER_UTILS    //
//////////////////////

///////////////////////////  LEXICAL_UTILS   ///////////////////////////
int						count_tokens(char **tokens);
void					print_tokens(char **scripts_line, int count);
void					printer_split(char **tokens);
bool					is_alphanumeric(char c);

///////////////////////////  SEMANTIC_UTILS   ///////////////////////////
bool					ft_isexecutable(char *executable);
struct s_ast			*find_end_right(struct s_ast *node);
struct s_ast			*handle_not_right(struct s_minishell *minishell,
							struct s_ast *ast);
struct s_ast			*handle_not_right_2(struct s_minishell *minishell,
							struct s_ast *ast);
bool					is_sub_tree(int export_fg, struct s_token_stream *prev,
							struct s_token_stream *tmp);

///////////////////////////     AST_UTILS    ///////////////////////////
bool					ast_is_assign(struct s_ast *ast);
bool					ast_not_right_type(struct s_ast *ast);
struct s_ast			*find_prev(struct s_ast *node, char *token_name);
struct s_ast			*ast_lookup(struct s_ast *node, char *token_name);
bool					is_child(int root, struct s_token_stream *tmp);

///////////////////////////     TREE_UTILS   ///////////////////////////
void					structure(struct s_ast *root, int level );

///////////////////////////     AST_HELP_FUNCS   ///////////////////////////
bool					is_bracket(struct s_minishell *minishell, char *str);

///////////////////////////     DOLLAR_SIGN   ///////////////////////////
char					*string_dollar_sign(char *str);

///////////////////////////     TREE_BUILDER   ///////////////////////////
bool					export(struct s_minishell *minishell,
							struct s_token_stream *prev);
bool					a_right(struct s_ast *ast,
							struct s_minishell *minishell);
void					advance(struct s_token_stream **prev,
							struct s_token_stream **tmp);
struct s_ast			*check_bracket_and_assign(struct s_minishell *minishell,
							struct s_token_stream **stm);

////////////////////
//  EXECUTE_UTILS //
////////////////////

void					file_reader(int fd_in);
void					rise_error_and_exit(struct s_ast *ast);
void					print_file(char *file);
void					new_line_remove(char *line);
int						ast_child_num(struct s_ast *node);

bool					is_builtin_ast(char *cmd);
bool					ast_is_simple(struct s_ast *ast);
int						openfile(char *file, int re_or_wr);

char					**command_statement_create(struct s_ast *ast);
void					command_statement_execute(char **command_statement,
							char *path,
							struct s_minishell *minishell, int fd_out);
char					*get_path(char *cmd, t_env *env);
bool					a_err(struct s_minishell *m, char *var, int value);
void					command_run(char **command_statement,
							char *command_path,
							struct s_minishell *m, struct s_ast *ast);

//francisco shit
int						ignore_inside_special(char *string, char special);
char					*ft_cutter(char *string, int n_byte);
int						in_special( char c, char *special);
int						words_count(char *string, char split_char,
							char *special);
int						increase_i(char *string, char split_char,
							char *special);
bool					quotes_string_check(char **scripts_line, int num);
char					**ft_new_split(char *string, char split_char,
							char *special);
void					printer_split(char **tokens);

bool					ft_iscommand(char *str, t_env *env);
bool					ft_isfile(char *str);
bool					ft_isword(char *str);
void					printer_variable(struct s_variable *variable);

void					print_the_env(t_env *enviroment);

void					minishell_process_command_pipe(struct s_ast *ast,
							struct s_minishell *minishell, int type);
void					freeme(char **paths);
void					parentesis_open(struct s_data *d);
static void				open_true_dollarsign(struct s_data *d);
static void				closed_true_dollarsign(struct s_data *d);

#endif