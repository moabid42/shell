/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:24:11 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/26 22:09:08 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "libft.h"

int	found_split_char(int i, bool *word)
{
	i++;
	(*word) = false;
	return (i);
}

int	found_char_to_ignore(int *word_count, int i, char *string, bool *word)
{
	if ((*word) == false)
		(*word_count)++;
	(*word) = true;
	if (string[i + 1])
		return (i = i + 2);
	else
	{
		(*word_count)++;
		i++;
	}
	return (i);
}

int	found_word(bool *word, int i, int *word_count)
{
	if ((*word) == false)
		(*word_count)++;
	(*word) = true;
	return (++i);
}

int	reader_word_count(char *string, t_args *args)
{
	int		i;
	int		n;
	bool	word;

	i = 0;
	word = false;
	n = 0;
	while (string[i])
	{
		if (ft_strchr(args->ign_char_inside, string[i]) != NULL)
			i += jump_char_inside(&string[i], args->ign_char_inside, &n, &word);
		else if (ft_strchr(args->ignore, string[i]) != NULL)
			i = found_char_to_ignore(&n, i, string, &word);
		else if (single_word_strchr(args->single_word, &string[i]) > 0)
		{
			i += (single_word_strchr(args->single_word, &string[i]));
			n++;
			word = false;
		}
		else if (ft_strchr(args->split_char, string[i]) != NULL)
			i = found_split_char(i, &word);
		else
			i = found_word(&word, i, &n);
	}
	return (n);
}
