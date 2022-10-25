/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:54:45 by moabid            #+#    #+#             */
/*   Updated: 2022/10/25 20:39:49 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

void	print_tokens(char **scripts_line, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("The token value is : %s\n", scripts_line[i]);
		i++;
	}
}

void	printer_split(char **tokens)
{
	while (*tokens)
	{
		dprintf(2, "The token is : %s\n", *tokens);
		tokens++;
	}
}

bool	is_alphanumeric(char c)
{
	if (('0' <= c && c <= '9') || \
		('a' <= c && c <= 'z') || \
		('A' <= c && c <= 'Z'))
		return (true);
	return (false);
}
