/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:22:52 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/26 16:31:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "libft.h"

void	init_var(int *i, int *j, bool *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

int	check_for_word(char *string, t_args *args)
{
	int		i;
	int		n;
	bool	word;

	init_var(&i, &n, &word);
	while (string[i])
	{
		if (ft_strchr(args->ign_char_inside, string[i]) != NULL)
			i += jump_char_inside(&string[i], args->ign_char_inside, &n, &word);
		else if (ft_strchr(args->ignore, string[i]) != NULL)
			i = found_char_to_ignore(&n, i, string, &word);
		else if (single_word_strchr(args->single_word, &string[i]) > 0)
			return (i);
		else if (ft_strchr(args->split_char, string[i]) != NULL)
		{
			found_split_char(i, &word);
			return (i);
		}
		else
			i = found_word(&word, i, &n);
		if (word == false)
			return (i);
	}
	return (i);
}

char	*create_the_word(char *string, int n)
{
	int		i;
	char	*new_string;

	i = 0;
	new_string = malloc((sizeof(char)) * n);
	if (new_string == NULL)
		return (NULL);
	while (i < n)
	{
		new_string[i] = string[i];
		i++;
	}
	new_string[n] = '\0';
	return (new_string);
}
