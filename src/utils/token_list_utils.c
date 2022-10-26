/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:13:45 by frame             #+#    #+#             */
/*   Updated: 2022/10/26 10:22:04 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct s_token_stream	*stack_create(struct s_minishell *minishell,
				char **tokens, unsigned int count)
{
	int						i;
	struct s_token_stream	*new_node;
	struct s_token_stream	*curr;

	i = 0;
	new_node = (struct s_token_stream *) ft_malloc(sizeof(
				struct s_token_stream));
	curr = new_node;
	minishell->single = false;
	while (i < count)
	{
		if (i < count - 1)
			new_node->next = (struct s_token_stream *) ft_malloc(sizeof(
						struct s_token_stream));
		if (!my_strcmp("\'\'", tokens[i]))
			minishell->single = true;
		new_node->token_name = quotes_remover(tokens[i], "\"'", minishell);
		new_node->token_type = find_type(tokens[i], minishell);
		new_node->closed = false;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

void	garbage_collect_token(struct s_token_stream *lst)
{
	if (lst == NULL)
		return ;
	free(lst->token_name);
	free(lst);
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
