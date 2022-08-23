/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:24:34 by frmessin          #+#    #+#             */
/*   Updated: 2022/08/20 12:14:20 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env *change_value(t_env *node)
{
	char *pivot;
	pivot = node->name;
	node->name = (node->next)->name;
	(node->next)->name = pivot;
	pivot = node->content;
	node->content = (node->next)->content;
	(node->next)->content = pivot;
	return (node);
}

t_env *alphabetic_order(t_env *head)
{
	t_env *tmp;
	bool changes;
	changes = true;
	while(changes)
	{
		tmp = head;
		changes = false;
		while(tmp->next != NULL)
		{
			if(!string_value_cmp(tmp->name,(tmp->next)->name))
			{
				tmp = change_value(tmp);
				changes = true;
			}
			tmp = tmp->next;
		}
	}
	return (head);
}