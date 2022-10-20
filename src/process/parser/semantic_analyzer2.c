/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:27:00 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 16:22:31 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "parser.h"
#include "utils.h"

char	*find_return_expend(struct s_minishell *minishell, char return_var)
{
	if (return_var == '?')
		return (ft_itoa(minishell->return_value));
	return (NULL);
}

char	*minishell_find_variable(struct s_minishell *minishell, char *variable)
{
	struct s_variable	*iterator;
	char				*expend_var;
	t_env				*tmp;
	int					i;

	iterator = minishell->variables;
	expend_var = "!?_";
	tmp = minishell->env;
	i = 0;
	while (iterator)
	{
		if (my_strcmp(iterator->var, variable + 1) == 0)
			return (iterator->value);
		iterator = iterator->next;
	}
	while (tmp)
	{
		if (!my_strcmp(tmp->name, variable + 1))
			return (tmp->content);
		tmp = tmp->next;
	}
	while (expend_var[i])
	{
		if (variable[1] == expend_var[i])
			return (find_return_expend(minishell, expend_var[i]));
		i++;
	}
	return (NULL);
}

bool	ft_isexecutable(char *executable)
{
	struct s_stat	*buf;

	buf = malloc(sizeof(struct s_stat));
	if (stat(executable, buf) == 0)
	{
		if (buf->st_mode & S_IXUSR)
		{
			free(buf);
			return (true);
		}
	}
	free(buf);
	return (false);
}

struct s_ast	*ast_create_first_node( \
		struct s_minishell *minishell, struct s_token_stream *token_stream)
{
	struct s_ast	*tmp;

	tmp = ft_malloc(sizeof(struct s_ast));
	if (token_stream->token_type == VARIABLE)
	{
		tmp->value.token_name = minishell_find_variable(minishell, \
			token_stream->token_name);
		tmp->value.token_type = WORD;
		if (tmp->value.token_name == NULL)
			tmp->value.token_name = ft_strdup("");
	}	
	else
	{
		tmp->value.token_name = token_stream->token_name;
		tmp->value.token_type = token_stream->token_type;
	}
	if (tmp->value.token_type == WORD || tmp->value.token_type == VARIABLE)
	{		
		if (ft_iscommand(tmp->value.token_name, minishell->env) == true
			|| ft_isexecutable(tmp->value.token_name) == true)
			tmp->value.token_type = COMMAND;
		else if (is_builtin(tmp->value.token_name) == true
			|| !my_strcmp(tmp->value.token_name, "exit"))
			tmp->value.token_type = BUILTIN;
	}
	tmp->isroot = true;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

bool	is_child(int root, struct s_token_stream *tmp)
{
	if (tmp->token_type < DOUBLE_SMALLER)
		return (false);
	if (tmp->token_type == PIPE && root == EQUAL)
		return (true);
	if (tmp->token_type > root)
		return (true);
	return (false);
}
