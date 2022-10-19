/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:20:26 by moabid            #+#    #+#             */
/*   Updated: 2022/10/18 22:16:17 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

struct scripts *ft_create_stack_scripts(char **scripts_line, unsigned int count) {
	int i;
	struct scripts *new_node;
	struct scripts *curr;

	i = 0;
	new_node = (struct scripts *) ft_malloc(sizeof(struct scripts));
	curr = new_node;
	while (i < count) {
		if (i < count - 1)
			new_node->next = (struct scripts *) ft_malloc(sizeof(struct scripts));
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

enum token_type find_redirection(char *token)
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

enum token_type find_var_shit(char *token) {
	if (token[0] == '$')
		return (VARIABLE);
	else
		return (EQUAL);
}

enum token_type find_logicalop(char *token) {
	if (!my_strcmp(token, "&&"))
		return (ANDAND);
	else
		return (OROR);
}

enum token_type find_bool(char *token) {
	if (!my_strcmp(token, "true"))
		return (TRUE);
	else
		return (FALSE);
}

enum token_type find_type(char *token)
{
	if (!my_strcmp(token, "|"))
		return (PIPE);
	else if (!my_strcmp(token, ">") || !my_strcmp(token, "<")
		   || !my_strcmp(token, ">>") || !my_strcmp(token, "<<"))
		return (find_redirection(token));
	else if (!my_strcmp(token, "&&") || !my_strcmp(token, "||"))
		return (find_logicalop(token));
	else if (token[0] == '$' || ft_strchr(token, '='))
		return (find_var_shit(token));
	else if (!my_strcmp(token, "*"))
		return (STAR);
	else if (!my_strcmp(token, "false") || !my_strcmp(token, "true"))
		return (find_bool(token));
	return (WORD);
}

struct token_stream *ft_create_stack_tkstream(struct minishell *minishell, char **tokens, unsigned int count) {
	int i;
	struct token_stream *new_node;
	struct token_stream *curr;

	i = 0;
	new_node = (struct token_stream *) ft_malloc(sizeof(struct token_stream));
	curr = new_node;
	while (i < count) {
		if (i < count - 1)
			new_node->next = (struct token_stream *) ft_malloc(sizeof(struct token_stream));
		new_node->token_name = tokens[i];
		new_node->token_type = find_type(tokens[i]);
		// if (new_node->token_type == EQUAL)
		// 	save_variable(minishell, new_node->token_name);
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

void printer(struct scripts *scripts) {
	struct scripts *tmp;
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

void printer_token(struct token_stream *scripts) {
	struct token_stream *tmp;
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

struct scripts *ft_create_node_script(char *cmd)
{
	struct scripts *new_node;

	new_node = malloc(sizeof(struct scripts));
	new_node->input_line = ft_strdup(cmd);
	new_node->next = NULL;
	return (new_node);
}

void garbage_collect_token(struct token_stream *lst) {
	if (lst == NULL)
		return;
	free(lst->token_name);
	free(lst);
}