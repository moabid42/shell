/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:20:26 by moabid            #+#    #+#             */
/*   Updated: 2022/10/17 14:09:31 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/utils.h"

struct s_token_stream	*ft_create_stack_tkstream(
		struct s_minishell *minishell, char **tokens, unsigned int count)
{
	int						i;
	struct s_token_stream	*new_node;
	struct s_token_stream	*curr;

	i = 0;
	new_node = (struct s_token_stream *) ft_malloc(
			sizeof(struct s_token_stream));
	curr = new_node;
	while (i < count)
	{
		if (i < count - 1)
			new_node->next = (struct s_token_stream *) ft_malloc(
					sizeof(struct s_token_stream));
		new_node->token_name = tokens[i];
		new_node->token_type = find_type(tokens[i]);
		new_node->closed = false;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	printer(struct s_scripts *scripts)
{
	struct s_scripts	*tmp;
	int					i;

	tmp = scripts;
	i = 0;
	while (tmp)
	{
		printf("[%s] -> ", tmp->input_line);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

void	printer_token(struct s_token_stream *scripts)
{
	struct s_token_stream	*tmp;
	int						i;

	tmp = scripts;
	i = 0;
	while (tmp)
	{
		printf("TOKEN [[%d]]: [%s] -> [%d] : {%d}\n",
			i, tmp->token_name, tmp->token_type, tmp->closed);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

struct s_scripts	*ft_create_node_script(char *cmd)
{
	struct s_scripts	*new_node;

	new_node = malloc(sizeof(struct s_scripts));
	new_node->input_line = ft_strdup(cmd);
	new_node->next = NULL;
	return (new_node);
}
