/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:53:55 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 21:54:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void padding ( char ch, int n )
{
  int i;

  for (i = 0; i < n; i++)
    putchar(ch);
}

void structure ( struct ast *root, int level )
{
  if (root == NULL)
  {
    padding('\t', level );
    puts("~");
  }
  else
  {
    structure(root->right, level + 1 );
    padding('\t', level);
    printf("%s[%d][%d]\n", root->value.token_name, root->value.token_type, root->value.exit_status);
    structure(root->left, level + 1);
  }
}