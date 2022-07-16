/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:05:17 by moabid            #+#    #+#             */
/*   Updated: 2022/07/13 16:57:27 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

#define SYNTAX_ERROR 	"[-] syntax error: format ./minishell"
#define MINI_INIT_ERROR "[-] error: Envirement variable error"
#define PARSE_ERROR		"[-] error: User input error"

#define NAME			"minishell"
#define	PROMPT			"esh"
#define PROMPT_TITLE	"PS1"


void	ft_error(char *str);
int		my_strcmp(const char *strg1, char *strg2);

#endif