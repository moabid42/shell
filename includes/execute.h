/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:42:04 by moabid            #+#    #+#             */
/*   Updated: 2022/08/08 23:48:27 by moabid           ###   ########.fr       */
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

#endif