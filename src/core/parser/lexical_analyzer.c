/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/10/26 03:33:01 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	minishell_scripts_parse(struct s_minishell *minishell)
{
	char	**scripts_line;

	if (minishell->input_str[0] == ';')
		return (!error_exit(minishell, "syntax error near unexpected token \
			`;'\n", NULL, 258));
	scripts_line = ft_new_split(minishell->input_str, ';', "\"'");
	minishell->scripts_num = words_count(minishell->input_str, ';', "\"'");
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line,
				minishell->scripts_num);
	if (minishell->scripts == NULL)
		return (false);
	return (true);
}

void	sanitize_token_stream(struct s_token_stream *token_stream)
{
	struct s_token_stream	*prev;

	prev = token_stream;
	while (token_stream)
	{
		if (!my_strcmp(token_stream->token_name, "")
			&& token_stream->next && token_stream->next->token_name[0] == '$')
		{
			prev->next = token_stream->next;
			free(token_stream);
			token_stream = prev->next;
		}
		else if (!my_strcmp(token_stream->token_name, "")
			&& prev->token_name[0] == '$')
		{
			prev->next = token_stream->next;
			free(token_stream);
			token_stream = prev->next;
		}
		else
		{
			prev = token_stream;
			token_stream = token_stream->next;
		}
	}
}

struct s_token_stream	*token_stream_create(struct s_minishell *minishell,
		char **tokens, struct s_scripts *script)
{
	struct s_token_stream	*token_stream;

	token_stream = stack_create(minishell, tokens, script->tokens_num);
	script->token_stream = token_stream;
	sanitize_token_stream(token_stream);
	if (token_checker(token_stream, minishell) == true)
		return (NULL);
	if (have_multi_redi(token_stream) == true)
		token_stream_remove(&token_stream);
	if (can_be_arranged(token_stream) == true
		|| can_be_arranged_left(token_stream) == true)
		token_stream_rearrange(&token_stream);
	return (token_stream);
}

struct s_token_stream	*lexical_analyzer_create(struct s_scripts *script,
		struct s_minishell *minishell)
{
	char				**tokens;
	t_args				args;

	args.split_char = " \t\b\r\v\f";
	args.single_word = (char *[]){"(", ")", "||", "&&", "|", "&&",
		"<<", ">>", "<", ">", NULL};
	args.ignore = (char *)"\\";
	args.ign_char_inside = (char *)"\"'";
	if (check_paired_quotes(script->input_line) == false)
		return (NULL);
	if (have_dollar_var(script->input_line, minishell) == true)
		script->input_line = string_dollar_sign(script->input_line);
	tokens = ft_reader(script->input_line, &args);
	script->tokens_num = reader_word_count(script->input_line, &args);
	if (star_exist(tokens) == true)
	{
		tokens = token_expend_star(tokens, script->tokens_num - 1);
		script->tokens_num = count_tokens(tokens);
	}
	return (token_stream_create(minishell, tokens, script));
}
