/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:42:04 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:14:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "builtin.h"
# include "utils.h"
# include "parser.h"
# include "minishell.h"	
# define MAX_SIZE 9223372036854775806
# define MIN_SIZE -9223372036854775807

struct	ast;
struct	minishell;

enum	e_direction {
	LEFT,
	RIGHT
};

enum	e_redirection {
	DIRECT,
	OVERWRITE,
	APPEND
};

int		minishell_ast_execute(struct ast *ast, struct minishell *minishell);
char	**command_statement_create(struct ast *ast);
void	command_statement_destroy(char **command_statement);
void	minishell_process_pipeline(struct ast *ast, struct minishell *minishell);
int	ast_child_num(struct ast *node);

int	openfile(char *file, int re_or_wr);


void	minishell_process_rediraction_open(struct ast *ast, struct minishell *minishell);
void	command_statement_execute_complexe(struct ast *ast, struct minishell *minishell);

bool	is_builtin(char *cmd);
void	builtin_run(char **cmd_list, struct minishell *minishell);
void	builtin_run_ast(struct ast *ast, struct minishell *minishell);

void	minishell_save_variable(char *variable_assigned, struct minishell *minishell);

void structure ( struct ast *root, int level );

///////////////////
//    heredoc    //
///////////////////

struct ast	*ast_seek_end(struct ast *ast);
void	heredoc_statement_execute(struct ast *ast,
			struct minishell *minishell, int out);
void	heredoc_forward_command(struct ast *ast, struct minishell *minishell);
void	heredoc_execute_caller(struct ast *tmp, int direction);
void	execute_heredoc(char *delimiter, int magic);

///////////////////
//  stat_execut  //
///////////////////

void	less_statement_execute(char **command_statement,
			struct ast *ast, struct minishell *minishell, int fd_out);
int	get_fd_out(struct ast *ast, struct ast **jump);

///////////////////
//  tree_crossi  //
///////////////////

int	child_n_c(struct ast *node);
char	**duplicate_right_left(struct ast *tmp, int *i, char **cmds);
void	command_statement_destroy(char **command_statement);
void	correct_args(char **cmds, struct minishell *minishell);
int	minishell_ast_execute(struct ast *ast, struct minishell *minishell);

///////////////////
//    tree_run   //
///////////////////

void	minishell_process_pipeline(struct ast *ast, struct minishell *minishell);
void	minishell_process_bool(struct ast *ast, struct minishell *minishell);
void	minishell_process_command(struct ast *ast, struct minishell *m);
void	minishell_run_equal(struct ast *ast, struct minishell *minishell);
void	builtin_run_ast(struct ast *ast, struct minishell *minishell);

///////////////////
//   variables   //
///////////////////

struct s_variable	*variable_create(char **variable_list);
void	variable_insert_node(struct s_variable *variable,
			struct s_variable *list);
bool	minishell_var_lookup(char *var_str, struct s_variable *variable);
void	minishell_save_variable(char *variable_assigned,
		struct minishell *minishell);
void	printer_variable(struct s_variable *variable);

///////////////////
//    builtin    //
///////////////////

bool	is_builtin(char *cmd);
void	builtin_run(char **cmd_list, struct minishell *minishell);

///////////////////
//  pipe_process //
///////////////////

void	process_pipe_run_left(struct ast *ast, struct minishell *minishell);
void	process_pipe_run_right(struct ast *ast, struct minishell *minishell);
void	minishell_process_command_pipe(struct ast *ast,
			struct minishell *minishell, int type);
void	process_pipe_run_first(struct ast *ast,
			struct ast *first, struct minishell *minishell, int fd_out);

///////////////////
//  redirection  //
///////////////////

bool	redirection_exist(struct ast *ast);
void	process_redirect_left(struct ast *ast);
void	process_direct(struct ast *ast, struct minishell *minishell);
void	process_redirect_overwrite(struct ast *ast, struct minishell *minishell);
void	process_redirect_append(struct ast *ast, struct minishell *minishell);

///////////////////
//  tree_execut  //
///////////////////

void	command_statement_run(char **command_statement,
			char *command_path, struct minishell *minishell);
char	**command_statement_create_complexe(struct ast *ast);
void	command_statement_execute_complexe(struct ast *ast,
			struct minishell *minishell);
void	redirection_run(struct ast *ast, struct ast *first,
			struct minishell *minishell, int fd_out);

#endif