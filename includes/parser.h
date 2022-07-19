/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 12:56:03 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"
#include "utils.h"

struct minishell;

enum token_type {
	WORD,
	FLAG,

	VARIABLE,
	EQUAL,

	SIGNLE_QUOTES,
	DOUBLE_QUOTES,
	BACKSLASH,
	
	PARENTHS,
	SQUARE_BRACKETS,
	CURLY_BRACKERTS,

	LOGICAL_OP,
	WILDCARD,

	PIPE,
	REDIRACTION,

	SPACE,
	OTHER
};

struct scripts {
	char	*input_line;
	int		tokens_num;
	struct token_stream *token_stream;
	struct scripts	*next;
};

struct token_stream {
	char	*token_name;
	enum	token_type token_type;
	struct token_stream *next;	
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

bool	minishell_scripts_parse(struct minishell *minishell);
void	token_stream_destroy(struct minishell *minishell);
void	minishell_scripts_destory(struct minishell *minishell);

void	lexical_analyzer_create(struct minishell *minishell);
void	token_stream_create(struct minishell *minishell);
void	token_stream_destory(struct minishell *minishell);
void	lexical_analyzer_destroy(struct minishell *minishell);


void	syntax_analyzer_create(struct minishell *minishell);
void	syntax_analyzer_destroy(struct minishell *minishell);

void	semantic_analyzer_create(struct minishell *minishell);
void	semantic_analyzer_destroy(struct minishell *minishell);




#endif
