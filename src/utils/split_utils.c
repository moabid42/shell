/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 00:12:23 by moabid            #+#    #+#             */
/*   Updated: 2022/07/18 20:48:10 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include "utils.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int					ft_isalpha(int c);
// size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);;
// void				*ft_malloc(size_t size);
// void				ft_bzero(void *s, size_t n);
// void				*ft_memset(void *b, int c, size_t n);

// int	ft_isspace(int c)
// {
// 	return (c == '\f' || c == '\n' || c == '\r' \
// 	|| c == '\t' || c == '\v' || c == ' ');
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	ft_memset(s, 0, n);
// }

// void	*ft_memset(void *b, int c, size_t n)
// {
// 	unsigned char	*dest;
// 	unsigned char	src;
// 	size_t			i;

// 	dest = b;
// 	src = c;
// 	i = 0;
// 	while (i++ < n)
// 		*dest++ = src;
// 	return (b);
// }


// void	*ft_malloc(size_t size)
// {
// 	void	*ptr;

// 	ptr = malloc(size);
// 	if (ptr)
// 		ft_bzero(ptr, size);
// 	else
// 	{
// 		free(ptr);
// 		exit(1);
// 	}
// 	return (ptr);
// }

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
		if (ft_isalpha(s[i]))
			while (s[i] && ft_isalpha(s[i]))
				i++;
		else if (!ft_isspace(s[i]))
			i++;
		else
			while (s[i] && ft_isspace(s[i]))
				i++;
	}
	if (ft_isspace(s[i- i]))
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
		while ((*next_str)[i] && ft_isalpha((*next_str)[i]))
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

char	**ft_split_tokens(struct scripts *script)
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

// int main(void)
// {
// 	int index;
// 	char	random[] = "what'is     '/ this' fu''cking'sh it' ";
// 	char **strs;

// 	printf("--------> [%s]\n", random);
// 	strs = ft_split_tokens(random);
// 	index = get_nb_tokens(random);
// 	printf("%d\n", index);
// }