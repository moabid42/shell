/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/18 22:20:03 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"
#include "utils.h"

struct minishell;

struct scripts {
	char	*input_line;
	int		tokens_num;
	struct token_stream *token_stream;
	struct scripts	*next;
};

struct token_stream {
	char	*token_name;
	char	*attr_value;	
	struct token_stream *next;	
};

struct syntax_tree {
	
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


void	lexical_analyzer_create(struct minishell *minishell, struct token_stream *token_stream);
void	token_stream_create(struct minishell *minishell);
void	token_stream_destory(struct minishell *minishell);
void	lexical_analyzer_destroy(struct token_stream *token_stream);


void	syntax_analyzer_create(struct token_stream *token_stream, struct syntax_tree *syntax_tree);
void	syntax_analyzer_destroy(struct syntax_tree *syntax_tree);		

void	semantic_analyzer_create(struct syntax_tree *syntax_tree, struct ast *ast);
void	semantic_analyzer_destroy(struct ast *ast);




#endif
