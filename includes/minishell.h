/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:00:09 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 02:19:39 by moabid           ###   ########.fr       */
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

struct ast;
struct scripts;
enum e_redirection;
typedef struct s_env t_env;

enum e_type {
    SIMPLE,
    COMPLEXE
};

struct s_variable {
	char *var;
	char *value;
	struct s_variable *next;
};

struct minishell {
	t_env			*env;
	char			**g_env;
	char			*prompt; // can be changed when exporting PS1
	char			*input_str;
	int				input_len;
	enum    		e_type type;
	int				return_value;
	int				open;
	bool		 	start_right;
	bool			handled;
	bool			single;
	bool			dollar_in;
	bool			export_fg;
	int				fd_out;
	long long		byte_code;
	long long		brakets_flag;
	int				index_flag;
	struct	s_variable *variables;
	enum	e_redirection redirection;
	unsigned int scripts_num;
	struct	scripts *scripts;
};

////////////////////
//   INPUT_PROC   //
////////////////////

void	minishell_ast_execute_subshells(struct ast *ast, struct minishell *minishell);
void	syntax_analyzer_run(struct ast *ast, struct minishell *minishell, struct token_stream *token_stream);
void	minishell_process_input(struct scripts *script, struct minishell *minishell);
void	minishell_destroy_input(struct scripts *script);
void	minishell_read_input(struct minishell *minishell);

////////////////////
// MINISHELL_INIT //
////////////////////

void    minishell_create(struct minishell *minishell, char **env);
void 	minishell_get_input(struct minishell *minishell);
char	*get_input_terminal(int fd);
void    minishell_destroy(struct minishell *minishell);

////////////////////
//  MINISHELL_RUN //
////////////////////

void	handle_weird(struct minishell *minishell);
bool	is_weird(char *str);
void    minishell_run(struct minishell *minishell);

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