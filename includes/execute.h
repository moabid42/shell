/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:42:04 by moabid            #+#    #+#             */
/*   Updated: 2022/10/16 17:25:44 by moabid           ###   ########.fr       */
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

int		minishell_ast_execute(struct s_ast *ast, struct s_minishell *minishell);
char	**command_statement_create(struct s_ast *ast);
void	command_statement_destroy(char **command_statement);
void	minishell_process_pipeline(
			struct s_ast *ast, struct s_minishell *minishell);
void	minishell_process_command(
			struct s_ast *ast, struct s_minishell *minishell);
int		ast_child_num(struct s_ast *node);

int		openfile(char *file, int re_or_wr);

void	minishell_process_rediraction_open(
			struct s_ast *ast, struct s_minishell *minishell);
void	command_statement_execute_complexe(
			struct s_ast *ast, struct s_minishell *minishell);

bool	is_builtin(char *cmd);
void	builtin_run(char **cmd_list, struct s_minishell *minishell);
void	builtin_run_ast(struct s_ast *ast, struct s_minishell *minishell);

void	minishell_save_variable(
			char *variable_assigned, struct s_minishell *minishell);

void structure ( struct ast *root, int level );

#endif