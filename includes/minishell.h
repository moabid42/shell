/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:09 by moabid            #+#    #+#             */
/*   Updated: 2022/08/23 21:25:47 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <termios.h>
#include "../src/utils/libft/libft.h"
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include "utils.h"
#include "parser.h"
#include "execute.h"
#include "../src/utils/libft/get_next_line.h"

struct ast;
struct scripts;
enum e_redirection;

struct s_variable {
	char *var;
	char *value;
	struct s_variable *next;
};	

typedef struct	s_env
{
	char *name;
	char *content;
	struct s_env	*next;
}				t_env;

struct minishell {
	char	**env;
	char	**g_env;
	char	*prompt; // can be changed when exporting PS1
	char	*input_str;
	bool	terminate;
	int		return_value;
	struct	s_variable *variables;
	enum	e_redirection redirection;
	unsigned int scripts_num;
	struct	scripts *scripts;
};

void    minishell_create(struct minishell *minishell, char **env);
void	minishell_get_input(struct minishell *minishell);
void    minishell_destroy(struct minishell *minishell);
void    minishell_run(struct minishell *minishell);
char	**minishell_env_init(char **env);
char	**ft_split_strings(char *str);

#endif