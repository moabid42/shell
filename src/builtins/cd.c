/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:05:01 by frmessin          #+#    #+#             */
/*   Updated: 2022/09/08 18:44:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	ft_cd(char **argv, struct minishell *minishell);
char	*get_home(t_env *env);

static	t_env *create_variable(t_env *env, char *name, char *path)
{
	t_env *new;
	
	new = new_node();
	new->name = name;
	new->content = path;
	env = append_new_node(env, new);
	return (env);
}

static void		update_current_pwd(char *path, char *old_path, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	printf("path: %s \n old_Path: %s\n", path, old_path);
	while(tmp && my_strcmp(tmp->name, "PWD"))
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
	while (tmp && my_strcmp(tmp->name, "OLDPWD"))
		tmp = tmp->next;
	if (tmp == NULL)
		*env = create_variable(*env, "OLDPWD", old_path);
	else
	{
		if(tmp->content)
			free(tmp->content);
		tmp->content = old_path;
	}
}

static char	*set_path(char	*old_path, char **argv, t_env *env)
{
	char *path;
	if(!argv[1])
		path = get_home(env);
	else
		path = (ft_strjoin(ft_strjoin(old_path, "/"), argv[1]));
	return (path);
}

char	*get_home(t_env *env)
{
	t_env *tmp;
	char *path;
	tmp = env;
	// while(env != NULL)
 	// {
	// 	if(env->name[0] == 'H' )
 	// 		printf("name: |%s|    content: |%s| \n", env->name, env->content);
 	// 	env = env->next;
 	// }
	env = tmp;
	while(env)
	{
		if (!my_strcmp(env->name, "HOME"))
		{
			path = ft_strdup(env->content);
			return path;
		}
		env = env->next;
	}
	return (NULL);
}

void		ft_cd(char **argv, struct minishell *minishell)
{
	char	*old_path;
	t_env	*tmp;
	char	*path;
	
	tmp = minishell->env;
	old_path = get_pwd();
	path = set_path(old_path, argv, minishell->env);
	if (path && chdir(path) == - 1)
			return ;
	else if (path == NULL && argv[1] == NULL)
		printf("home not set");
	else if (argv[1] && (chdir(path) == -1))
	{
		write(1, "wrong directory",15);
		return;
	}
	update_current_pwd(path, old_path, &tmp);
	return;
}
