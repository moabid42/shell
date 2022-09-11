/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:18:25 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/08 17:53:33 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env *append_new_node(t_env *enviroment, t_env *node)
{
	t_env *tmp;

	tmp = enviroment;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	return (enviroment);
}

t_env *fill_new_node(char *str, t_env *node)
{
	// printf("The string is : [%s]\n", str);
	if(check_string('=',str))
	{
		node->name = copy_till_bit(str, find_chr(str, '='));
		if(str[find_chr(str, '=')])
			node->content = copy_till_bit(&str[find_chr(str, '=') + 1], ft_strlen(str) - find_chr(str, '=') - 1);
		else
			node->content = "";
	}
	else
	{
		node->name = copy_till_bit(str, ft_strlen(str));
		node->content = NULL;
	}
	return (node);
}

t_env *new_node()
{
	t_env *node;
	node = malloc(sizeof(t_env));
	node->next = NULL;
	return (node);
}

t_env	*create_node(t_env *env, char *name, char *content)
{
	t_env *node;

	node = new_node();
	node->name = name;
	node->content = content;
	env = append_new_node(env, node);
	return (env);
}
