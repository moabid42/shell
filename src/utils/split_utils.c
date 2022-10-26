/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 00:12:23 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 10:20:17 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include "utils.h"

unsigned int	get_nb_tokens(char const *s)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s)
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		nb_strs++;
		if (ft_isalnum(s[i]))
			while (s[i] && ft_isalnum(s[i]))
				i++;
		else if (!ft_isspace(s[i]))
			i++;
		else
			while (s[i] && ft_isspace(s[i]))
				i++;
	}
	if (ft_isspace(s[i - i]))
		nb_strs++;
	return (nb_strs);
}

void	get_next_str(char **next_str, unsigned int *next_str_len)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	if (ft_isalpha((*next_str)[i]))
	{
		while ((*next_str)[i] && ft_isalnum((*next_str)[i]))
		{
			(*next_str_len)++;
			i++;
		}
		return ;
	}
	else if (!ft_isspace((*next_str)[i]))
	{
		(*next_str_len)++;
		i++;
		return ;
	}
	else
	{
		while ((*next_str)[i] && ft_isspace((*next_str)[i]))
		{
			(*next_str_len)++;
			i++;
		}
		return ;
	}
}

char	**ft_split_tokens(struct s_scripts *script)
{
	char			**tokens;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_tokens;
	int				i;

	i = 0;
	if (!script->input_line)
		return (NULL);
	nb_tokens = get_nb_tokens(script->input_line);
	tokens = ft_malloc(sizeof(char *) * nb_tokens);
	next_str = (char *)script->input_line;
	next_str_len = 0;
	while (i < (int)nb_tokens)
	{
		get_next_str(&next_str, &next_str_len);
		tokens[i] = ft_malloc(sizeof(char) * (next_str_len + 1));
		ft_strlcpy(tokens[i], next_str, next_str_len + 1);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
