/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:53:19 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 21:55:34 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isexecutable(char *executable)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (stat(executable, buf) == 0)
	{
		if (buf->st_mode & S_IXUSR)
		{
			free(buf);
			return (true);
		}
	}
	free(buf);
	return (false);
}

struct ast *find_end_right(struct ast *node)
{
	if (!node->right)
		return(node);
	node = node->right;
	while(node->left)
		node = node->left;
	return (node);
}

