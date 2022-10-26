/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:20:26 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:33:01 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct s_scripts *ft_create_stack_scripts(char **scripts_line, unsigned int count) {
	int i;
	struct s_scripts *new_node;
	struct s_scripts *curr;

	i = 0;
	new_node = (struct s_scripts *) ft_malloc(sizeof(struct s_scripts));
	curr = new_node;
	while (i < count) {
		if (i < count - 1)
			new_node->next = (struct s_scripts *) ft_malloc(sizeof(struct s_scripts));
		new_node->input_line = ft_strdup(scripts_line[i]);
		new_node->have_herdoc = 0;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

enum e_token_type find_redirection(char *token)
{
	if (!my_strcmp(token, ">"))
		return (GREATER);
	else if (!my_strcmp(token, "<"))
		return (LESS);
	else if (!my_strcmp(token, ">>"))
		return (DOUBLE_GREATER);
	else
		return (DOUBLE_SMALLER);
}

enum e_token_type	find_var_shit(char *token, struct s_minishell *minishell)
{
	if (token[0] == '$'
		&& (token[1] == '\0'
			|| token[1] == '\"'
			|| token[1] == '\''
			|| minishell->single == true))
		return (WORD);
	else if (token[0] == '$')
		return (VARIABLE);
	else
		return (EQUAL);
}

enum e_token_type find_logicalop(char *token) {
	if (!my_strcmp(token, "&&"))
		return (AND);
	else
		return (OR);
}

enum e_token_type find_bool(char *token) {
	if (!my_strcmp(token, "true"))
		return (TRUE);
	else
		return (FALSE);
}

enum e_token_type find_type(char *token, struct s_minishell *minishell)
{
	if (!my_strcmp(token, "|"))
		return (PIPE);
	else if (!my_strcmp(token, ">") || !my_strcmp(token, "<")
		|| !my_strcmp(token, ">>") || !my_strcmp(token, "<<"))
		return (find_redirection(token));
	else if (!my_strcmp(token, "&&") || !my_strcmp(token, "||"))
		return (find_logicalop(token));
	else if (token[0] == '$' || ft_strchr(token, '='))
		return (find_var_shit(token, minishell));
	else if (!my_strcmp(token, "*"))
		return (STAR);
	else if (!my_strcmp(token, "false") || !my_strcmp(token, "true"))
		return (find_bool(token));
	return (WORD);
}

bool	check_single(struct s_minishell *minishell, char c)
{
	// minishell->single = true;
	return (c == '\'');
}

char	*quotes_remover(char *str, char *set, struct s_minishell *minishell)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '$' && (str[1] == '\"' || check_single(minishell, str[1])))
		i = 1;
	new_str = (char *) ft_malloc(sizeof(char) * (ft_strlen(str) + 1 - i));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\"')
				new_str[j++] = str[i++];
		}
		else if (str[i] == '\\')
		{
			i++;
			if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
				new_str[j++] = str[i];
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

struct s_token_stream *stack_create(struct s_minishell *minishell, char **tokens, unsigned int count) {
	int i;
	struct s_token_stream *new_node;
	struct s_token_stream *curr;

	i = 0;
	new_node = (struct s_token_stream *) ft_malloc(sizeof(struct s_token_stream));
	curr = new_node;
	minishell->single = false;
	while (i < count)
	{
		if (i < count - 1)
			new_node->next = (struct s_token_stream *) ft_malloc(sizeof(struct s_token_stream));	
		if (!my_strcmp("\'\'", tokens[i]))
			minishell->single = true;
		new_node->token_name = quotes_remover(tokens[i], "\"'", minishell);
		new_node->token_type = find_type(tokens[i], minishell);
		new_node->closed = false;
		if (i == (count - 1))
			new_node->next = NULL;
		else
			new_node = new_node->next;
		i++;
	}
	return (curr);
}

void free_split(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void printer(struct s_scripts *scripts) {
	struct s_scripts *tmp;
	int i;

	tmp = scripts;
	i = 0;
	while (tmp) {
		printf("[%s] -> ", tmp->input_line);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

void printer_token(struct s_token_stream *scripts) {
	struct s_token_stream *tmp;
	int i;

	tmp = scripts;
	i = 0;
	while (tmp) {
		printf("TOKEN [[%d]]: [%s] -> [%d] : {%d}\n", i, tmp->token_name, tmp->token_type, tmp->closed);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}

struct s_scripts *ft_create_node_script(char *cmd)
{
	struct s_scripts *new_node;

	new_node = malloc(sizeof(struct s_scripts));
	new_node->input_line = ft_strdup(cmd);
	new_node->next = NULL;
	return (new_node);
}

void garbage_collect_token(struct s_token_stream *lst) {
	if (lst == NULL)
		return;
	free(lst->token_name);
	free(lst);
}