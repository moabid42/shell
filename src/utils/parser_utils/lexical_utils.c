/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:54:45 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 23:37:17 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

void	print_tokens(char **scripts_line, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		printf("The token value is : %s\n", scripts_line[i]);
		i++;
	}
}

void	printer_split(char **tokens)
{
	while(*tokens)
	{
		dprintf(2, "The token is : %s\n", *tokens);
		tokens++;
	}
}

char *string_dollar_sign(char *string)
{
	int		i;
	bool	open;
	char	quotes_type;

	i = 0;
	open = false;
	while(string[i]){
		if(string[i] = '\'' || string[i] = '\"')
	}
}