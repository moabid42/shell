/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:35:33 by moabid            #+#    #+#             */
/*   Updated: 2022/03/27 17:35:08 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	size_t	h_len;
	size_t	size;

	if (*needle == '\0')
		return ((char *)haystack);
	n_len = ft_strlen(needle);
	h_len = ft_strlen(haystack);
	if (h_len < n_len || len < n_len)
		return (0);
	size = len;
	while (size-- >= n_len || !needle)
	{
		if (ft_memcmp(haystack, needle, n_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (0);
}
