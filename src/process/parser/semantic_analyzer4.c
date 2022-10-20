/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:29:30 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 16:29:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

struct s_ast	*node_create_parent(struct s_token_stream *tmp)
{
	struct s_asdt *node;

	node = ft_malloc(sizeof(struct s_ast));
	node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ast_insert_parent(struct s_ast *node, struct s_ast **root, struct s_minishell *minishell)
{
	struct s_ast *tmp;

	tmp = (*root)->right;
	if (node->value.token_type <= (*root)->value.token_type
	|| ((node->value.token_type / 2 == 0)
	&& (node->value.token_type / 2 == 0)))
	{
		node->isroot = true;
		node->left = *root;
		*root = node;
	}
	else
	{
		(*root)->right = node;
		node->left = tmp;
	}
}

struct s_ast	*node_create_child(struct s_token_stream *tmp, struct s_minishell *minishell, int prev_type)
{
	struct s_ast *node;

	node = ft_malloc(sizeof(struct s_ast));
	if (node_contain_special(tmp->token_name, '\"') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\"', ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special(tmp->token_name, '\'') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\'', ft_strlen(tmp->token_name) - 1);
	else if (node_contain_special_single(tmp->token_name, '\\') == true)
		node->value.token_name = ft_special_trim(tmp->token_name, '\\', ft_strlen(tmp->token_name));	
	else if (tmp->token_type == VARIABLE)
	{
		node->value.token_name = minishell_find_variable(minishell, tmp->token_name);
		if (node->value.token_name == NULL)
			node->value.token_name = ft_strdup("");
	}
	else
		node->value.token_name = tmp->token_name;
	node->value.token_type = tmp->token_type;
	if (node->value.token_type == WORD
		|| node->value.token_type == VARIABLE)
	{
		if (ft_iscommand(node->value.token_name, minishell->env) == true
			&& (prev_type < GREATER || prev_type == EQUAL))
			node->value.token_type = COMMAND;
		else if (ft_isfile(node->value.token_name) == true)
			node->value.token_type = FILES;
	}
	node->isroot = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

bool	ast_not_right_type(struct s_ast *ast)
{
	return (ast->value.token_type == COMMAND 
		|| ast->value.token_type == DOUBLE_SMALLER
		|| ast->value.token_type == LESS
		|| ast->value.token_type == PIPE
		|| ast->value.token_type == ANDAND
		|| ast->value.token_type == OROR
		|| ast->value.token_type == TRUE
		|| ast->value.token_type == FALSE
		|| ast->value.token_type == GREATER
		|| ast->value.token_type == DOUBLE_GREATER
		|| ast->value.token_type == EQUAL
		|| is_builtin(ast->value.token_name)
		|| !my_strcmp(ast->value.token_name, "exit"));
}

void	padding( char ch, int n )
{
	int	i;

	i = 0;
	while (i < n)
	{
		putchar(ch);
		i++;
	}
}
