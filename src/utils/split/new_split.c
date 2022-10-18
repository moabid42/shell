/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 22:52:20 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/18 13:24:13 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

char	*manage_word(int *start, char *string, char *special, char split_char)
{
	int		i;
	int		special_index;
	char	*word;

	i = *start;
	while (string[i] != split_char && string[i] != '\0')
	{
		if (in_special(string[i], special) >= 0)
		{
			special_index = in_special(string[i], special);
			i += ignore_inside_special(&string[i], special[special_index]);
			if (string[i] != '\0')
				i++;
		}
		else
			i++;
	}
	word = ft_cutter (&string[*start], i - *start);
	*start = i;
	return (word);
}

char	**ft_new_split(char *string, char split_char, char *special)
{
	int		i;
	int		tab;
	char	**split_string;

	split_string = malloc(sizeof(char *) * words_count(
				string, split_char, special) + 1);
	if (split_string == NULL)
		return (NULL);
	tab = 0;
	i = 0;
	while (i < ft_strlen(string))
	{
		if (string[i] != split_char)
		{
			split_string[tab] = manage_word(&i, string, special, split_char);
			tab++;
		}
		i++;
	}	
	split_string[tab] = NULL;
	return (split_string);
}
