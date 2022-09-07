/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:05:01 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/07 18:47:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void		ft_cd(char **argv, struct minishell *minishell);

static	t_env *create_variable(t_env *env, char *name, char *path)
{
	t_env *new;
	
	new = new_node();
	new->name = name;
	new->content = path;
	env = append_new_node(env, new);
	return (env);
}

static bool		update_current_pwd(char *path, char *old_path, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while(tmp && !my_strcmp(tmp->name, "PWD"))
		tmp = tmp->next;
	if (tmp == NULL)
		*env = create_variable(*env, "PWD", path);
	else
	{
		if(tmp->content)
			free(tmp->content);
		tmp->content = path; 
	}
	tmp = *env;
	while(tmp && !my_strcmp(tmp->name, "OLDPWD"))
		tmp=tmp->next;
	if(tmp == NULL)
		*env = create_variable(*env, "OLDPWD", old_path);
	else
	{
		if(tmp->content)
			free(tmp->content);
		tmp->content = old_path;
	}
	return (true);
}

// static DIR		*check_cd(char **argv, t_env *env)
// {
// 	t_env	*tmp;
// 	DIR	*dir;

// 	tmp = env;
// 	if(!argv[1])
// 	{
// 		while(tmp && !my_strcmp(tmp->name, "HOME"))
// 			tmp=tmp->next;
// 		if (tmp == NULL)
// 		{
// 			write(1,"kaine zu hause :(",17);
// 			return (false); 
// 		}
// 		dir = opendir(tmp->content);
// 	}
// 	dir = opendir(argv[1]);
// 	return (dir);
// }

static char	*set_path( char **argv, t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	if(!argv[1])
	{
		while(tmp && !my_strcmp(tmp->name, "HOME"))
			tmp=tmp->next;
		return (tmp->content);
	}
	else
		return(argv[1]);
}

void		ft_cd(char **argv, struct minishell *minishell)
{
	// char	*dir;
	char	*old_path;
	char	*path;

	//dir = check_cd(argv, minishell->env);
	// dir = NULL;
	path = set_path(argv, minishell->env);
	old_path = get_pwd();
	if(path == NULL && argv[1] == NULL)
	{
		printf("home not set");
	}
	if (path && (chdir(path) == -1))
	{
		write(1, "wrong directory",15);
		exit(0);

	}
	if (update_current_pwd(path, old_path, &minishell->env) == false)
		exit(0);
	// while(env != NULL)
 	// {
 	// 	printf("name: |%s|    content: |%s| \n", (minishell->env)->name, (minishell->env)->content);
 	// 	(minishell->env) = (minishell->env)->next;
 	// }
	exit(0);
}

// int		main(int argc,	char **argv, char **env)
// {
// 	int		error;
// 	t_env	*enviroment;
// 	enviroment = create_the_env(env);
// 	error = ft_cd( argc, argv, enviroment);
// 	return (error);
// }