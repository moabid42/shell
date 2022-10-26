/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:20:26 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 10:39:59 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct s_scripts	*ft_create_stack_scripts(
		char **scripts_line, unsigned int count)
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

/*minishell->single = true;*/
bool	check_single(struct s_minishell *minishell, char c)
{
	return (c == '\'');
}

char	*quotes_remover(char *str, char *set, struct s_minishell *minishell)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '$' && (str[1] == '\"' || check_single(minishell, str[1])))
		i = 1;
	new_str = (char *) ft_malloc(sizeof(char) * (ft_strlen(str) + 1 - i));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\"')
				new_str[j++] = str[i++];
		}
		else if (str[i] == '\\')
		{
			i++;
			if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
				new_str[j++] = str[i];
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
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

struct s_scripts	*ft_create_node_script(char *cmd)
{
	struct s_scripts	*new_node;

	new_node = malloc(sizeof(struct s_scripts));
	new_node->input_line = ft_strdup(cmd);
	new_node->next = NULL;
	return (new_node);
}
