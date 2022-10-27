/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:09 by moabid            #+#    #+#             */
/*   Updated: 2022/10/27 22:45:57 by moabid           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

struct					s_ast;
struct					s_scripts;
enum					e_redirection;
typedef struct s_env	t_env;

enum e_type {
	SIMPLE,
	COMPLEXE
};

struct s_variable {
	char				*var;
	char				*value;
	struct s_variable	*next;
};

struct s_data {
	int		i;
	int		j;
	bool	open;
	char	q_type;
	char	*ret_str;
	char	*str;
};

struct s_minishell {
	t_env					*env;
	char					**g_env;
	char					*input_str;
	int						input_len;
	enum e_type				type;
	int						return_value;
	int						open;
	bool					start_right;
	bool					handled;
	bool					single;
	bool					dollar_in;
	bool					export_fg;
	bool					cat_fg;
	bool					no_path;
	int						is_weird_cat;
	int						fd_out;
	int						pids[1000];
	int						pid_count;
	int						pipe_count;
	long long				byte_code;
	long long				brakets_flag;
	int						index_flag;
	struct s_variable		*variables;
	enum e_redirection		redirection;
	unsigned int			scripts_num;
	struct s_scripts		*scripts;
};

////////////////////
//   INPUT_PROC   //
////////////////////

void	minishell_ast_execute_subshells(struct s_ast *ast,
			struct s_minishell *minishell);
void	syntax_analyzer_run(struct s_ast *ast,
			struct s_minishell *minishell, struct s_token_stream *token_stream);
void	minishell_process_input(struct s_scripts *script,
			struct s_minishell *minishell);
void	minishell_destroy_input(struct s_scripts *script);
void	minishell_read_input(struct s_minishell *minishell);

////////////////////
// MINISHELL_INIT //
////////////////////

void	minishell_create(struct s_minishell *minishell, char **env);
void	minishell_get_input(struct s_minishell *minishell);
char	*get_input_terminal(int fd);
void	minishell_destroy(struct s_minishell *minishell);
bool	both_quote(char *str);

////////////////////
//  MINISHELL_RUN //
////////////////////

void	handle_weird(struct s_minishell *minishell);
bool	is_weird(char *str);
void	minishell_run(struct s_minishell *minishell);

////////////////////
// MINISHELL_SEGN //
////////////////////

int		termios_echoback(bool echo_ctl_chr);
void	handler(int sig);
void	signal_run(int sig);

////////////////////
//   ENVIROMENT   //
////////////////////

t_env	*minishell_env_init(char **env);
t_env	*create_the_env(char **env);
void	print_the_env(t_env *enviroment);

char	*copy_till_bit(char *str, int n_byte);
char	**split_name_content(char *str);
int		list_len(t_env *env);
char	*make_env_string(t_env *env);
char	**e_to_s(t_env *env);

#endif