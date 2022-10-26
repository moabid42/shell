/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frame <frame@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:53:55 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 09:27:51 by frame            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	padding(char ch, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		putchar(ch);
	}
}

void	structure(struct s_ast *root, int level)
{
	if (root == NULL)
	{
		padding('\t', level);
		puts("~");
	}
	else
	{
		structure(root->right, level + 1);
		padding('\t', level);
		printf("%s[%d][%d]\n", root->value.token_name,
			root->value.token_type, root->value.exit_status);
		structure(root->left, level + 1);
	}
}
