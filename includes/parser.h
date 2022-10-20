/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/16 17:29:43 by moabid           ###   ########.fr       */
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

enum	e_token_type {
	ANDAND,
	OROR,
	PIPE,
	GREATER,
	DOUBLE_GREATER,
	LESS,
	DOUBLE_SMALLER,
	COMMAND,
	BUILTIN,
	FILES,
	FALSE,
	TRUE,
	EQUAL,
	VARIABLE,
	STAR,
	STAR_WORD,
	WORD,
	STRING_DOUBLE,
	STRING_SINGLE,
	BACKSLASH,
	PARENTHS_OP,
	PARENTHS_CL,
	SQUARE_BRACKETS_OP,
	SQUARE_BRACKETS_CL,
	CURLY_BRACKERTS_OP,
	CURLY_BRACKERTS_CL,
	EXCAMATION,
	QUESTION,
};

struct s_scripts {
	char					*input_line;
	unsigned int			tokens_num;
	int						exit_status;
	int						have_herdoc;
	char					*delimiter;
	struct s_token_stream	*token_stream;
	struct s_scripts		*next;
};

struct s_token_stream {
	char					*token_name;
	enum e_token_type		token_type;
	bool					in_string;
	bool					closed;
	struct s_token_strea	*next;
};

struct s_AST_value {
	char					*token_name;
	enum e_token_type		token_type;

};

struct s_ast {
	bool					isroot;
	struct s_AST_value		value;
	struct s_ast			*right;
	struct s_ast			*left;
};

/*  ENUMS   */
enum e_token_type			find_type(char *token);
enum e_token_type			find_logicalop(char *token);
enum e_token_type			find_var_shit(char *token);
enum e_token_type			find_pipe_or_space(char *token);
enum e_token_type			find_rediraction(char *token);
enum e_token_type			find_wildcard(char *token);
enum e_token_type			find_quotes(char *token);
enum e_token_type			find_parenth(char *token);

void						minishell_read_input(struct s_minishell *minishell);
bool						minishell_scripts_parse(
								struct s_minishell *minishell);
void						minishell_scripts_destory(
								struct s_minishell *minishell);
void						minishell_destroy_input(struct s_scripts *script);
void						minishell_process_input(
								struct s_scripts *script,
								struct s_minishell *minishell);
struct s_token_stream		*lexical_analyzer_create(
								struct s_scripts *script,
								struct s_minishell *minishell);
void						lexical_analyzer_destroy(
								struct s_token_stream **token_stream);
void						syntax_analyzer_create(
								struct s_token_stream *token_stream,
								struct s_scripts *script);
void						syntax_analyzer_destroy(
								struct s_minishell *minishell);
struct s_ast				*semantic_analyzer_create(
								struct s_minishell *minishell,
								struct s_token_stream *token_stream);
void						semantic_analyzer_destroy(
								struct s_minishell *minishell);

#endif
