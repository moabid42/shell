/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:52:43 by moabid            #+#    #+#             */
/*   Updated: 2022/04/10 23:25:57 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*new_d;
	char	*new_s;
	size_t	i;

	if (!dest && !src)
		return (0);
	new_d = (char *)dest;
	new_s = (char *)src;
	i = 0;
	while (i < n--)
		*new_d++ = *new_s++;
	return (dest);
}
