/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:09 by moabid            #+#    #+#             */
/*   Updated: 2022/10/16 17:37:20 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "utils.h"
# include "parser.h"
# include "execute.h"
# include "builtin.h"
# include "../src/utils/libft/libft.h"
# include "../src/utils/libft/get_next_line.h"
# include "../src/utils/libft/reader.h"

struct					s_ast;
struct					s_scripts;
enum					e_redirection;
typedef struct s_env	t_env;

enum e_type {
	SIMPLE,
	COMPLEXE
};

struct s_variable {
	char					*var;
	char					*value;
	struct s_variable		*next;
};

/*  g_env can be changed when exporting PS1*/
struct s_minishell {
	t_env					*env;
	char					**g_env;
	char					*prompt;
	char					*input_str;
	int						input_len;
	enum e_type				type;
	int						return_value;
	long long				byte_code;
	long long				brakets_flag;
	int						index_flag;
	struct s_variable		*variables;
	enum e_redirection		redirection;
	unsigned int			scripts_num;
	struct s_scripts		*scripts;
};

void	minishell_create(struct s_minishell *minishell, char **env);
void	minishell_get_input(struct s_minishell *minishell);
void	minishell_destroy(struct s_minishell *minishell);
void	minishell_run(struct s_minishell *minishell);
t_env	*minishell_env_init(char **env);
char	**ft_split_strings(char *str);
void	signal_run(int sig);

#endif