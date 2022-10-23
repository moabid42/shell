/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmessin <frmessin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/10/23 23:04:50 by frmessin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool minishell_scripts_parse(struct minishell *minishell)
{
	char	**scripts_line;

	if (minishell->input_str[0] == ';')
		return(!error_exit(minishell, "syntax error near unexpected token `;'\n", NULL, 258));
	scripts_line = ft_new_split(minishell->input_str, ';', "\"'");
	minishell->scripts_num = words_count(minishell->input_str,';', "\"'");
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line, minishell->scripts_num);
	if (minishell->scripts == NULL)
		return (false);
	return (true);
}

bool	token_checker(struct token_stream *stream, struct minishell *minishell)
{
	struct token_stream	*tmp;
	bool				bracket;

	tmp = stream;
	bracket = false;
	while (stream)
	{
		if (stream->token_name[0] == '<'
			&& tmp->token_name[0] == '>')
			return (error_exit(minishell, "esh: syntax error near unexpected token `<'\n", NULL, 258));
		if (stream->token_name[0] == '(')
			bracket = true;
		else if (stream->token_name[0] == ')')
			bracket = false;
		tmp = stream;
		stream = stream->next;
	}
	if (tmp->token_name[0] == '<'
		&& stream == NULL)
		return (error_exit(minishell, "esh: syntax error near unexpected token `newline'\n", NULL, 258));
	if (bracket == true)
		return (error_exit(minishell, "esh: syntax error near unexpected token `)'\n", NULL, 258));
	return (false);
}

static bool	check_paired_quotes(char *string){
	int	i;
	bool open;
	char quotes_type;

	i = 0;
	open = false;
	while (string[i]){
		if ((string[i] == '\'' || string[i] == '\"') && open == false)
		{
			open = true;
			quotes_type = string[i];
		}
		else if ((string[i] == quotes_type) && open == true)
		{
			open = false;
		}
		i++;
	}
	if (open == true)
		return (false);
	else
		return (true);
}

struct token_stream *lexical_analyzer_create(struct scripts *script, struct minishell *minishell)
{
	char **tokens;
	struct token_stream *token_stream;
	t_args args;
	
	args.split_char = " ";
	args.single_word = (char *[]){"(", ")", "||", "&&", "|", "&&", "<<", ">>", "<", ">", NULL};
	args.ignore = (char *)"\\";
	args.ign_char_inside = (char *)"\"'";
	if(check_paired_quotes(script->input_line) == false)
		return (NULL);
	tokens = ft_reader(script->input_line, &args);
	// int i;
	// i = 0;
	// while(tokens[i]){
	// 	ft_putstr(tokens[i]);
	// 	i++;
	//	}
	script->tokens_num = reader_word_count(script->input_line, &args);
	if (star_exist(tokens) == true)
	{
		tokens = token_expend_star(tokens, script->tokens_num - 1);
		script->tokens_num = count_tokens(tokens);
	}
	token_stream = ft_create_stack_tkstream(minishell, tokens, script->tokens_num);
	script->token_stream = token_stream;
	if (token_checker(token_stream, minishell) == true)
		return (NULL);
	// /*TOKEN PRINTER*/
	// while(token_stream){
	// 	ft_putstr(token_stream->token_name);
	// 	token_stream = token_stream->next;
	// }
	return (token_stream);
}
