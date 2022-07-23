/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 18:31:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"
#include "utils.h"

struct minishell;
struct scripts;

enum token_type {
	WORD,
	FLAG,

	VARIABLE,
	EQUAL,

    	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	BACKSLASH,
	
	PARENTHS_OP,
	PARENTHS_CL,
	SQUARE_BRACKETS_OP,
    	SQUARE_BRACKETS_CL,
	CURLY_BRACKERTS_OP,
    	CURLY_BRACKERTS_CL,

	ANDAND,
	OROR,

	STAR,
	EXCAMATION,
	QUESTION,

	PIPE,
	SPACE,

	GREATER,
	LESS,
	DOUBLE_GREATER,
	DOUBLE_SMALLER,

	OTHER
};

struct scripts {
	char               	*input_line;
	unsigned int		tokens_num;
	bool				have_herdoc;
	struct token_stream 	*token_stream;
	struct scripts	    	*next;
};

struct token_stream {
	char	*token_name;
	enum	token_type 		token_type;
	bool				closed;
	struct token_stream	*next;
};

struct syntax_stream {

};

struct ast {
	
};

// struct commands {
// 	char *command;
// 	struct commands *next;
// };

// struct piped_cmds {
// 	char *piped_cmd;
// 	struct piped_cmds *next;
// };

// enums
enum	token_type find_type(char *token);

enum	token_type find_logicalop(char *token);
enum	token_type find_var_shit(char *token);
enum	token_type find_pipe_or_space(char *token);
enum	token_type find_rediraction(char *token);
enum	token_type find_wildcard(char *token);
enum	token_type find_quotes(char *token);
enum	token_type find_parenth(char *token);




void	minishell_read_input(struct minishell *minishell);
bool	minishell_scripts_parse(struct minishell *minishell);
void	minishell_scripts_destory(struct minishell *minishell);


void	minishell_destroy_input(struct scripts *script);
void	minishell_process_input(struct scripts *script);


struct token_stream	*lexical_analyzer_create(struct scripts *script);
void	lexical_analyzer_destroy(struct token_stream **token_stream);


void	syntax_analyzer_create(struct token_stream *token_stream, struct scripts *script);
void	syntax_analyzer_destroy(struct minishell *minishell);

void	semantic_analyzer_create(struct minishell *minishell);
void	semantic_analyzer_destroy(struct minishell *minishell);




#endif
