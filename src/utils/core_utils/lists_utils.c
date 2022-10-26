/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:20:26 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 16:53:42 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct s_scripts	*ft_create_stack_scripts(char **scripts_line,
			unsigned int count)
{
	int					i;
	struct s_scripts	*new_node;
	struct s_scripts	*curr;

	i = 0;
	new_node = (struct s_scripts *) ft_malloc(sizeof(struct s_scripts));
	curr = new_node;
	while (i < count)
	{
		if (i < count - 1)
			new_node->next = (struct s_scripts *)
				ft_malloc(sizeof(struct s_scripts));
		new_node->input_line = ft_strdup(scripts_line[i]);
		new_node->have_herdoc = 0;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

static void	quotes_advance(char *str, char **new_str, int *i, int *j)
{
	if (str[(*i)] == '\'' || str[(*i)] == '\"')
	{
		(*i)++;
		while (str[(*i)] != '\'' && str[(*i)] != '\"')
			(*new_str)[(*j)++] = str[(*i)++];
	}
	else if (str[*i] == '\\')
	{
		(*i)++;
		if (str[(*i)] == '\'' || str[(*i)] == '\"' || str[(*i)] == '\\')
			(*new_str)[(*j)++] = str[(*i)];
	}
	else
		(*new_str)[(*j)++] = str[(*i)];
}

char	*quotes_remover(char *str, char *set, struct s_minishell *minishell)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '$' && (str[1] == '\"' || str[1] == '\''))
		i = 1;
	new_str = (char *) ft_malloc(sizeof(char) * (ft_strlen(str) + 1 - i));
	while (str[i])
	{
		quotes_advance(str, &new_str, &i, &j);
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

struct s_token_stream	*stack_create(struct s_minishell *minishell,
						char **tokens, unsigned int count)
{
	int						i;
	struct s_token_stream	*new_node;
	struct s_token_stream	*curr;

	i = -1;
	new_node = (struct s_token_stream *)ft_malloc
		(sizeof(struct s_token_stream));
	curr = new_node;
	minishell->single = false;
	while (++i < count)
	{
		if (i < count - 1)
			new_node->next = (struct s_token_stream *)
				ft_malloc(sizeof(struct s_token_stream));
		if (!my_strcmp("\'\'", tokens[i]))
			minishell->single = true;
		new_node->token_name = quotes_remover(tokens[i], "\"'", minishell);
		new_node->token_type = find_type(tokens[i], minishell);
		new_node->closed = false;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
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
