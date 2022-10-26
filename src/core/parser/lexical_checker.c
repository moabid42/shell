/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:38:33 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 20:56:15 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_checker(struct token_stream *stream, struct minishell *minishell)
{
	struct token_stream	*tmp;
	bool				bracket;

	tmp = stream;
	bracket = false;
	while (stream)
	{
		if (stream->token_name[0] == '(' && tmp->token_name[0] == ')')
			return (error_exit(minishell, "esh: syntax error near unexpected token \
				`('\n", NULL, 258));
		else if (stream->token_name[0] == '<' && tmp->token_name[0] == '>')
			return (error_exit(minishell, "esh: syntax error near unexpected token \
				`<'\n", NULL, 258));
		if (stream->token_name[0] == '(')
			bracket = true;
		else if (stream->token_name[0] == ')')
			bracket = false;
		tmp = stream;
		stream = stream->next;
	}
	if (tmp->token_name[0] == '<'
		&& stream == NULL)
		return (error_exit(minishell, "esh: syntax error near unexpected token\
			`newline'\n", NULL, 258));
	if (bracket == true)
		return (error_exit(minishell, "esh: syntax error near unexpected token\
			 `)'\n", NULL, 258));
	return (false);
}

bool	check_paired_quotes(char *string)
{
	int		i;
	bool	open;
	char	quotes_type;

	i = 0;
	open = false;
	while (string[i])
	{
		if ((string[i] == '\'' || string[i] == '\"') && open == false)
		{
			open = true;
			quotes_type = string[i];
		}
		else if ((string[i] == quotes_type) && open == true)
		{
			open = false;
		}
		i++;
	}
	if (open == true)
		return (false);
	else
		return (true);
}

bool	have_dollar_var(char *string, struct minishell *minishell)
{
	int	i;

	i = 0;
	check_flag_dollar(string, minishell);
	while (string[i])
	{
		if (string[i] == '$' && is_alphanumeric(string[i + 1]))
			return (true);
		i++;
	}
	return (false);
}

void	check_flag_dollar(char *str, struct minishell *minishell)
{
	int	i;

	i = 0;
	minishell->dollar_in = false;
	while (str[i])
	{
		if (str[i] != ' ' && str[i + 1] == '$')
		{
			minishell->dollar_in = true;
			return ;
		}
		i++;
	}
}
