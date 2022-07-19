/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/07/19 13:03:10 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	minishell_scripts_parse(struct minishell *minishell)
{
	char	**scripts_line;
	int		i;

	i = 0;
	scripts_line = ft_split(minishell->input_str, ';');
	// printf("]]]]]]      %s\n", scripts_line[0]);
	// printf("[[[[]]]]       %s\n", scripts_line[1]);
	minishell->scripts_num = ft_get_nb_strs(minishell->input_str, ';');
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line, minishell->scripts_num);
	free_split(scripts_line);
	if (minishell->scripts == NULL)
		return (false);
	return (true);
}

void	token_stream_create(struct minishell *minishell)
{
	struct scripts		*tmp;
	int					i;
	char				**tokens;
	
	i = 0;
	tmp = minishell->scripts;
	while (i < minishell->scripts_num)
	{
		tokens = ft_split_tokens(tmp);
		tmp->tokens_num = get_nb_tokens(tmp->input_line);
		tmp->token_stream = ft_create_stack_tkstream(tokens, tmp->tokens_num);
		printer_token(tmp->token_stream);
		tmp = tmp->next;
		i++;
	}
}

void	lexical_analyzer_create(struct minishell *minishell)
{
	if (!minishell_scripts_parse(minishell))
		ft_error(UNEXPECTED_TOKEN);
	token_stream_create(minishell);
	exit(0);
}

void	token_stream_destroy(struct minishell *minishell)
{
	
}

void	minishell_scripts_destroy(struct minishell *minishell)
{
	
}

void	lexical_analyzer_destroy(struct minishell *minishell)
{
	token_stream_destroy(minishell);
	minishell_scripts_destroy(minishell);
}