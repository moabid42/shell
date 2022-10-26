/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:53:55 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 13:20:10 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void printer(struct s_scripts *scripts)
// {
// 	struct s_scripts	*tmp;
// 	int					i;

// 	tmp = scripts;
// 	i = 0;
// 	while (tmp)
// 	{
// 		printf("[%s] -> ", tmp->input_line);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	printf("\n");
// }

// void printer_token(struct s_token_stream *scripts)
// {
// 	struct s_token_stream	*tmp;
// 	int						i;

// 	tmp = scripts;
// 	i = 0;
// 	while (tmp)
// 	{
// 		printf("TOKEN [[%d]]: [%s] -> [%d] : {%d}\n", i,
//			tmp->token_name, tmp->token_type, tmp->closed);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	printf("\n");
// }

// static void	padding(char ch, int n )
// {
// 	int	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		putchar(ch);
// 		i++;
// 	}
// }

// void	structure(struct s_ast *root, int level)
// {
// 	if (root == NULL)
// 	{
// 		padding('\t', level);
// 		puts("~");
// 	}
// 	else
// 	{
// 		structure(root->right, level + 1);
// 		padding('\t', level);
// 		printf("%s[%d][%d]\n", root->value.token_name,
// 				root->value.token_type, root->value.exit_status);
// 		structure(root->left, level + 1);
// 	}
// }
