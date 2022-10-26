/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:25:16 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 10:26:39 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_run_ast(struct s_ast *ast, struct s_minishell *minishell)
{
	char	**cmd_list;

	cmd_list = command_statement_create(ast);
	if (!my_strcmp(cmd_list[0], "exit"))
		ft_exit(cmd_list, minishell);
	else if (!my_strcmp(cmd_list[0], "cd"))
		ft_cd(cmd_list, minishell);
	else if (!my_strcmp(cmd_list[0], "export"))
		ft_export(cmd_list, minishell);
	else if (!my_strcmp(cmd_list[0], "unset"))
		ft_unset(cmd_list, minishell);
}

void	minishell_run_equal(struct s_ast *ast, struct s_minishell *minishell)
{
	minishell_save_variable(ast->value.token_name, minishell);
	if (ast->right)
		minishell_ast_execute(ast->right, minishell);
	else
		minishell_ast_execute(ast->left, minishell);
}

void	minishell_process_command(struct s_ast *ast, struct s_minishell *m)
{
	struct s_ast	*jump;
	char			**command_statement;
	char			*command_path;

	jump = ast;
	if (ast->value.token_type == WORD && a_err(m, ast->value.token_name, 127))
		return ;
	m->fd_out = get_fd_out(ast, &jump);
	if (m->fd_out == -1)
		return ;
	command_statement = command_statement_create(jump);
	if (ft_strchr(jump->value.token_name, '/') != NULL)
		command_path = ft_strdup(jump->value.token_name);
	else
		command_path = get_path(command_statement[0], m->env);
	if (command_path == NULL)
		command_path = jump->value.token_name;
	command_run(command_statement, command_path, m, ast);
	command_statement_destroy(command_statement);
}

void	minishell_process_bool(struct s_ast *ast, struct s_minishell *minishell)
{
	if (ast->value.token_type == FALSE)
		minishell->return_value = 1;
	else
		minishell->return_value = 0;
}

void	minishell_process_pipeline(struct s_ast *ast,
		struct s_minishell *minishell)
{
	minishell->type = COMPLEXE;
	if (ast->value.token_type == PIPE)
		minishell_process_command_pipe(ast, minishell, DIRECT);
	else if (ast->value.token_type == GREATER)
		minishell_process_command_pipe(ast, minishell, OVERWRITE);
	else
		minishell_process_command_pipe(ast, minishell, APPEND);
}
