/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:42:04 by moabid            #+#    #+#             */
/*   Updated: 2022/08/13 06:44:58 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "utils.h"
#include "parser.h"
#include "minishell.h"

struct ast;
struct minishell;

void	minishell_ast_execute(struct ast *ast, struct minishell *minishell);
char	**command_statement_create(struct ast *ast);
void	command_statement_destroy(char **command_statement);
void	minishell_process_pipeline(struct ast *ast, struct minishell *minishell);
void	minishell_process_command(struct ast *ast, struct minishell *minishell);
int	ast_child_num(struct ast *node);



void	minishell_process_rediraction_open(struct ast *ast, struct minishell *minishell);
void	command_statement_execute_complexe(struct ast *ast, struct minishell *minishell);

#endif