/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 04:59:32 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "utils.h"
# include "execute.h"
# include "builtin.h"

struct 	minishell;
struct 	scripts;

enum e_token_type
{
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
	DIRECTORY,
	FALSE,
	TRUE,
	EQUAL,
	VARIABLE,
	STAR,
	STAR_WORD,
	WORD
};

struct scripts {
    char 				*input_line;
    unsigned int 		tokens_num;
    int                 exit_status;
    int 				have_herdoc;
	char				*delimiter;
    struct token_stream *token_stream;
    struct scripts 		*next;
};

struct token_stream {
    char *token_name;
    enum token_type token_type;
	bool in_string;
    bool closed;
    struct token_stream *next;
};

struct AST_value {
    char    *token_name;
    int     exit_status;
    enum token_type token_type;
};

struct ast {
	bool	isroot;
    struct AST_value value;
    struct ast *right;
    struct ast *left;
};


// enums
enum token_type find_type(char *token);

enum token_type find_logicalop(char *token);

enum token_type find_var_shit(char *token);

enum token_type find_pipe_or_space(char *token);

enum token_type find_rediraction(char *token);

enum token_type find_wildcard(char *token);

enum token_type find_quotes(char *token);

enum token_type find_parenth(char *token);


void minishell_read_input(struct minishell *minishell);

bool minishell_scripts_parse(struct minishell *minishell);

void minishell_scripts_destory(struct minishell *minishell);


void minishell_destroy_input(struct scripts *script);

void minishell_process_input(struct scripts *script, struct minishell *minishell);


struct token_stream *lexical_analyzer_create(struct scripts *script, struct minishell *minishell);

void lexical_analyzer_destroy(struct token_stream **token_stream);


bool syntax_analyzer_create(struct token_stream *token_stream, struct ast *ast, struct  minishell *minishell);

void syntax_analyzer_destroy(struct minishell *minishell);

struct ast *semantic_analyzer_create(struct minishell *minishell, struct token_stream *token_stream);

void semantic_analyzer_destroy(struct minishell *minishell);

/////////////////////
//    AST_CREATE   //
/////////////////////

struct ast  *node_create_child(struct token_stream *tmp, struct minishell *minishell, int prev_type);
void        ast_insert_child(struct ast *node, struct ast **ast, struct token_stream *prev, struct minishell *minishell);

struct ast  *node_create_parent(struct token_stream *tmp);
void        ast_insert_parent(struct ast *node, struct ast **root, struct minishell *minishell);

/////////////////////
//  LEXICAL_ANAL   //
/////////////////////

bool                minishell_scripts_parse(struct minishell *minishell);
bool	            token_checker(struct token_stream *stream, struct minishell *minishell);
struct token_stream *lexical_analyzer_create(struct scripts *script, struct minishell *minishell);

/////////////////////
//  SYNTAX_ANAL    //
/////////////////////

bool                syntax_analyzer_create(struct token_stream *token_stream,
									struct ast *ast, struct minishell *minishell);

/////////////////////
//  SEMANTIC_ANAL  //
/////////////////////



/////////////////////
//    EXPEND_STAR  //
/////////////////////

int                 star_count_dirs(void);
int                 star_count(char **tokens);
void                star_expend_dir(char **new_tokens, int *i);
char                **token_expend_star(char **tokens, int prev_size);
bool                star_exist(char **tokens);

/////////////////////
//    EXPEND_VAR   //
/////////////////////

int                 isdir(const char* fileName);
char                *find_return_expend(struct minishell *minishell, char return_var);
char                *minishell_find_variable(struct minishell *minishell, char *variable);

/////////////////////
//    REORDERING   //
/////////////////////



#endif
