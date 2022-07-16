/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:45:59 by moabid            #+#    #+#             */
/*   Updated: 2022/07/14 22:01:41 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "minishell.h"
#include "utils.h"

struct input {
	struct commands commands;
	struct piped_cmds piped_cmds;
	struct minishell *minishell;
};

struct token_stream {
	char	*token_name;
	char	*attr_value;	
	struct token_stream *next;	
};

struct syntax_tree {
	
};

struct ast {
	
};

struct commands {
	char *command;
	struct commands *next;
};

struct piped_cmds {
	char *piped_cmd;
	struct piped_cmds *next;
};


#endif