/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:21:48 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 13:16:08 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/utils.h"

void	garbage_collect_token(struct s_token_stream *lst)
{
	if (lst == NULL)
		return ;
	free(lst->token_name);
	free(lst);
}
