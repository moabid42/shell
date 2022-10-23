/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:23:45 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/22 20:47:55 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "libft.h"

int	jump_char_inside(char *string, char *special, int *word_count, bool *word)
{
	char	*special_char;
	int		i;

	special_char = ft_strchr(special, string[0]);
	if (special_char == NULL)
		return (0);
	i = 1;
	while (string[i] && *special_char != string[i])
		i++;
	if (string[i] == *special_char)
		i++;
	if (*word == false)
		(*word_count)++;
	(*word) = true;
	return (i);
}

int	single_word_strchr( char **single_word, char *string)
{
	// printf("The string is :%s and the signle word is :%s\n", string, *single_word);
	bool	word;
	size_t	len;
	int		i;
	int		j;

	word = false;
	i = 0;
	while (single_word[i])
	{
		len = ft_strlen(single_word[i]);
		j = 0;
		while (string[j] && j < len)
		{
			if (string[j] == single_word[i][j])
				word = true;
			else
			{
				word = false;
				break ;
			}
			j++;
		}
		if (word == (true))
			return (len);
		i++;
	}
	// printf("The i is %d\n", len);
	// printf("The single word is %s\n", single_word[i]);
	return (word);
}
