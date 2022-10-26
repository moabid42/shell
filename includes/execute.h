/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:42:04 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 04:27:39 by moabid           ###   ########.fr       */
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

struct	s_ast;
struct	s_minishell;

enum	e_direction {
	LEFT,
	RIGHT
};

enum	e_redirection {
	DIRECT,
	OVERWRITE,
	APPEND
};

///////////////////
//    heredoc    //
///////////////////

struct s_ast		*ast_seek_end(struct s_ast *ast);
void				heredoc_statement_execute(struct s_ast *ast,
						struct s_minishell *minishell, int out);
void				heredoc_forward_command(struct s_ast *ast,
						struct s_minishell *minishell);
void				heredoc_execute_caller(struct s_ast *tmp, int direction);
void				execute_heredoc(char *delimiter, int magic);

///////////////////
//  stat_execut  //
///////////////////

void				less_statement_execute(char **command_statement,
						struct s_ast *ast, struct s_minishell *minishell,
						int fd_out);
int					get_fd_out(struct s_ast *ast, struct s_ast **jump);

///////////////////
//  tree_crossi  //
///////////////////

int					child_n_c(struct s_ast *node);
char				**duplicate_right_left(struct s_ast *tmp,
						int *i, char **cmds);
void				command_statement_destroy(char **command_statement);
void				correct_args(char **cmds, struct s_minishell *minishell);
int					minishell_ast_execute(struct s_ast *ast,
						struct s_minishell *minishell);

///////////////////
//    tree_run   //
///////////////////

void				minishell_process_pipeline(struct s_ast *ast,
						struct s_minishell *minishell);
void				minishell_process_bool(struct s_ast *ast,
						struct s_minishell *minishell);
void				minishell_process_command(struct s_ast *ast,
						struct s_minishell *m);
void				minishell_run_equal(struct s_ast *ast,
						struct s_minishell *minishell);
void				builtin_run_ast(struct s_ast *ast,
						struct s_minishell *minishell);

///////////////////
//   variables   //
///////////////////

struct s_variable	*variable_create(char **variable_list);
void				variable_insert_node(struct s_variable *variable,
						struct s_variable *list);
bool				minishell_var_lookup(char *var_str,
						struct s_variable *variable);
void				minishell_save_variable(char *variable_assigned,
						struct s_minishell *minishell);
void				printer_variable(struct s_variable *variable);

///////////////////
//    builtin    //
///////////////////

bool				is_builtin(char *cmd);
void				builtin_run(char **cmd_list, struct s_minishell *minishell);

///////////////////
//  pipe_process //
///////////////////

void				process_pipe_run_left(struct s_ast *ast,
						struct s_minishell *minishell);
void				process_pipe_run_right(struct s_ast *ast,
						struct s_minishell *minishell);
void				minishell_process_command_pipe(struct s_ast *ast,
						struct s_minishell *minishell, int type);
void				process_pipe_run_first(struct s_ast *ast,
						struct s_ast *first, struct s_minishell *minishell,
						int fd_out);

///////////////////
//  redirection  //
///////////////////

bool				redirection_exist(struct s_ast *ast);
void				process_redirect_left(struct s_ast *ast);
void				process_direct(struct s_ast *ast,
						struct s_minishell *minishell);
void				process_redirect_overwrite(struct s_ast *ast,
						struct s_minishell *minishell);
void				process_redirect_append(struct s_ast *ast,
						struct s_minishell *minishell);

///////////////////
//  tree_execut  //
///////////////////

void				command_statement_run(char **command_statement,
						char *command_path, struct s_minishell *minishell);
char				**command_statement_create_complexe(struct s_ast *ast);
void				command_statement_execute_complexe(struct s_ast *ast,
						struct s_minishell *minishell);
void				redirection_run(struct s_ast *ast, struct s_ast *first,
						struct s_minishell *minishell, int fd_out);

#endif