/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:20:26 by moabid            #+#    #+#             */
/*   Updated: 2022/07/22 18:10:14 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct scripts	*ft_create_stack_scripts(char **scripts_line, int count)
{
	int		i;
	struct scripts	*new_node;
	struct scripts	*curr;

	i = 0;
	new_node = (struct scripts *)ft_malloc(sizeof(struct scripts));
	curr = new_node;
	while (i < count)
	{
		if (i < count - 1)
			new_node->next = (struct scripts *)ft_malloc(sizeof(struct scripts));
		new_node->input_line = ft_strdup(scripts_line[i]);
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

struct token_stream	*ft_create_stack_tkstream(char **tokens, int count)
{
	int		i;
	struct token_stream	*new_node;
	struct token_stream	*curr;

	i = 0;
	new_node = (struct token_stream *)ft_malloc(sizeof(struct token_stream));
	curr = new_node;
	while (i < count)
	{
		if (i < count - 1)
			new_node->next = (struct token_stream *)ft_malloc(sizeof(struct token_stream));
		new_node->token_name= tokens[i];
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
	while(strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	printer(struct scripts *scripts)
{
	struct scripts *tmp;
	int		i;

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

void	printer_token(struct token_stream *scripts)
{
	struct token_stream *tmp;
	int		i;

	tmp = scripts;
	i = 0;
	while (tmp)
	{
		printf("TOKEN %d: [%s]\n", i, tmp->token_name);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

struct scripts	*ft_create_node_script(char *cmd)
{
	struct scripts	*new_node;
	
	new_node = (struct scripts *)ft_malloc(sizeof(struct scripts));
	new_node->input_line = ft_strdup(cmd);
	new_node->next = NULL;
	return (new_node);
}

void	garbage_collect_token(struct token_stream *lst)
{
	if (lst == NULL)
		return ;
	free(lst->token_name);
	free(lst);
}