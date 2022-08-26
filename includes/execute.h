/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:42:04 by moabid            #+#    #+#             */
/*   Updated: 2022/08/26 15:46:45 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "utils.h"
#include "parser.h"
#include "minishell.h"

# define MAX_SIZE 9223372036854775806
# define MIN_SIZE -9223372036854775807

struct ast;
struct minishell;

enum	e_direction {
	LEFT,
	RIGHT
};

enum	e_redirection {
	DIRECT,
	OVERWRITE,
	APPEND
};

void	minishell_ast_execute(struct ast *ast, struct minishell *minishell);
char	**command_statement_create(struct ast *ast);
void	command_statement_destroy(char **command_statement);
void	minishell_process_pipeline(struct ast *ast, struct minishell *minishell);
void	minishell_process_command(struct ast *ast, struct minishell *minishell);
int	ast_child_num(struct ast *node);

int	openfile(char *file, int re_or_wr);


void	minishell_process_rediraction_open(struct ast *ast, struct minishell *minishell);
void	command_statement_execute_complexe(struct ast *ast, struct minishell *minishell);

bool	is_builtin(char *cmd);
void	builtin_run(char **cmd_list, struct minishell *minishell);

#endif