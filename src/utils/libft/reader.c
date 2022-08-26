/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:11:34 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/26 21:50:27 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static int	word_maker(char *string, t_args *args, char **split)
{
	int	n;

	n = 0;
	if (check_for_word(string, args) > 0)
		n = check_for_word(string, args);
	else if (single_word_strchr(args->single_word, string) > 0)
		n = (single_word_strchr(args->single_word, string));
	*split = create_the_word(string, n);
	return (n);
}

static char	**fill_the_string(char **split, char *string,
		t_args *args, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (string[j])
		{
			if (check_for_word(&string[j], args) > 0)
			{
				j += word_maker(&string[j], args, &split[i]);
				break ;
			}
			if (single_word_strchr(args->single_word, &string[j]) > 0)
			{
				j += word_maker(&string[j], args, &split[i]);
				break ;
			}
			else
				j++;
		}
		i++;
	}
	return (split);
}

static char	**create_the_string(int size)
{
	char	**string;

	string = malloc((sizeof(char *) * size) + 1);
	if (string == NULL)
		return (NULL);
	string[size] = NULL;
	return (string);
}

char	**ft_reader(char *string, t_args *args)
{
	char	**split_string;

	split_string = create_the_string(reader_word_count(string, args));
	if (split_string == NULL)
		return (NULL);
	split_string = fill_the_string(split_string,
			string, args, reader_word_count(string, args));
	return (split_string);
}
