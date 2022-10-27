/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/27 02:01:32 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "utils.h"
# include "execute.h"
# include "builtin.h"

struct	s_minishell;
struct	s_scripts;

enum e_token_type
{
	AND,
	OR,
	PIPE,
	GREATER,
	DOUBLE_GREATER,
	LESS,
	DOUBLE_SMALLER,
	COMMAND,
	BUILTIN,
	FILES,
	DIRECTORY,
	FALSE,
	TRUE,
	EQUAL,
	VARIABLE,
	STAR,
	STAR_WORD,
	WORD
};

struct s_scripts
{
	char					*input_line;
	unsigned int			tokens_num;
	int						exit_status;
	int						have_herdoc;
	char					*delimiter;
	struct s_token_stream	*token_stream;
	struct s_scripts		*next;
};

struct s_token_stream
{
	char					*token_name;
	enum e_token_type		token_type;
	bool					in_string;
	bool					closed;
	struct s_token_stream	*next;
};

struct s_AST_value
{
	char				*token_name;
	int					exit_status;
	enum e_token_type	token_type;
};

struct s_ast {
	bool				isroot;
	struct s_AST_value	value;
	struct s_ast		*right;
	struct s_ast		*left;
};

// enums
enum e_token_type		find_type(char *token, struct s_minishell *minishell);

enum e_token_type		find_logicalop(char *token);

enum e_token_type		find_var_shit(char *token,
							struct s_minishell *minishell);

enum e_token_type		find_pipe_or_space(char *token);

enum e_token_type		find_rediraction(char *token);

enum e_token_type		find_wildcard(char *token);

enum e_token_type		find_quotes(char *token);

enum e_token_type		ind_parenth(char *token);

/////////////////////
//    AST_CREATE   //
/////////////////////

struct s_ast			*node_create_child(struct s_token_stream *tmp,
							struct s_minishell *minishell, int prev_type);
void					ast_insert_child(struct s_ast *node,
							struct s_ast **ast, struct s_token_stream *prev,
							struct s_minishell *minishell);
struct s_ast			*node_create_parent(struct s_token_stream *tmp);
void					ast_insert_parent(struct s_ast *node,
							struct s_ast **root,
							struct s_minishell *minishell);

/////////////////////
//  LEXICAL_ANAL   //
/////////////////////

bool					minishell_scripts_parse(struct s_minishell *minishell);
bool					token_checker(struct s_token_stream *stream,
							struct s_minishell *minishell);
struct s_token_stream	*lexical_analyzer_create(struct s_scripts *script,
							struct s_minishell *minishell);
struct s_scripts		*ft_create_node_script(char *cmd);

/////////////////////
//  SYNTAX_ANAL    //
/////////////////////

bool					syntax_analyzer_create(struct s_token_stream
							*token_stream,
							struct s_ast *ast, struct s_minishell *minishell);

/////////////////////
//  SEMANTIC_ANAL  //
/////////////////////

struct s_ast			*semantic_analyzer_create(struct s_minishell *minishell,
							struct s_token_stream *token_stream);
bool					check_for_pipes(struct s_token_stream *tmp);

/////////////////////
//    EXPEND_STAR  //
/////////////////////

int						star_count_dirs(void);
int						star_count(char **tokens);
void					star_expend_dir(char **new_tokens, int *i);
char					**token_expend_star(char **tokens, int prev_size);
bool					star_exist(char **tokens);

/////////////////////
//    EXPEND_VAR   //
/////////////////////

int						isdir(const char *fileName);
char					*find_return_expend(struct s_minishell *minishell,
							char return_var);
char					*minishell_find_variable(struct s_minishell *minishell,
							char *variable);

/////////////////////
//    REORDERING   //
/////////////////////

void					token_stream_remove(struct s_token_stream
							**token_stream);
bool					have_multi_redi(struct s_token_stream
							*token_stream);
bool					can_be_arranged_left(struct s_token_stream
							*token_stream);
bool					can_be_arranged(struct s_token_stream
							*token_stream);
void					token_stream_rearrange(struct s_token_stream
							**token_stream);

/////////////////////
//    FIRST_NODE   //
/////////////////////

struct s_ast			*ast_create_first_node(struct s_minishell *minishell,
							struct s_token_stream *token_stream);

/////////////////////
//    LEXICAL_CK   //
/////////////////////

void					check_flag_dollar(char *str,
							struct s_minishell *minishell);
bool					have_dollar_var(char *string,
							struct s_minishell *minishell);
bool					token_checker(struct s_token_stream *stream,
							struct s_minishell *minishell);
bool					check_paired_quotes(char *string);

#endif
