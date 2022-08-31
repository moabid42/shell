/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:21:22 by moabid            #+#    #+#             */
/*   Updated: 2022/08/27 04:44:00 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

// static void init_reader_struct(t_args *args)
// {
// 	// args->split_char = " ";
// 	// args->single_word = (char *[]){"||", "|", "&&", "<<", ">>", "<", ">", NULL};
// 	// args->ignore = (char *)"\\";
// 	// args->ign_char_inside = (char *)"\"'";
// }

void	print_tokens(char **scripts_line, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		printf("The token value is : %s\n", scripts_line[i]);
		i++;
	}
}

void	minishell_set_byte_code(struct minishell *minishell)
{
	long long	i;
	int			j;
	long long	edx;

	i = 1;
	i <<= 32;
	j = 0;
	edx = 0;
	while(j < minishell->input_len)
	{
		if (ft_strnstr(minishell->input_str + j, "&&", 3))
		{
			edx = edx | i;
			i *= 2;
			j += 2;
		}
		else if (ft_strnstr(minishell->input_str + j, "||", 3))
		{
			i *= 2;
			j += 2;
		}
		else
			j++;
	}
	minishell->byte_code = edx;
}

void decToBinary(long long n)
{
    int binaryNum[64];
	int	count = 0;
    int i = 0;

    while (n > 0)
	{
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
	{
		count++;
        printf("%d", binaryNum[j]);
	}
	printf("\nThe count is : %d\n", count);
}

bool minishell_scripts_parse(struct minishell *minishell)
{
	char	**scripts_line;
	t_args args;
	
	args.split_char = "&&";
	args.single_word = (char *[]){"||", "|", "<<", ">>", "<", ">", NULL};
	args.ignore = (char *)"\\";
	args.ign_char_inside = (char *)"\"'";
	scripts_line = ft_reader(minishell->input_str, &args);
	minishell->scripts_num = reader_word_count(minishell->input_str, &args);
	minishell_set_byte_code(minishell);
	printf("The dx register contain :\n");
	decToBinary(minishell->byte_code);
	if (minishell->scripts_num == 1)
		minishell->scripts = ft_create_node_script(scripts_line[0]);
	else
		minishell->scripts = ft_create_stack_scripts(scripts_line, minishell->scripts_num);
	free_split(scripts_line);
	if (minishell->scripts == NULL)
		return (false);
	minishell->scripts->exit_status = 0;
	return (true);
}

void	printer_split(char **tokens)
{
	while(*tokens)
	{
		dprintf(2, "The token is : %s\n", *tokens);
		tokens++;
	}
}

int	star_count_dirs(void)
{
	DIR				*dp;
	struct dirent	*dirp;
	int				count;

	count = 0;
	dp = opendir(".");
	if (dp == NULL)
		return (0);
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.')
			count++;
	}
	closedir(dp);
	return (count);
}

int	star_count(char **tokens)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (!my_strcmp(tokens[i], "*"))
			count++;
		i++;
	}
	return (count);
}

void	star_expend_dir(char **new_tokens, int *i)
{
	DIR				*dp;
	struct dirent	*dirp;

	dp = opendir(".");
	if (dp == NULL)
		return ;
	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.')
		{
			new_tokens[*i] = ft_strdup(dirp->d_name);
			(*i)++;
		}
	}
	closedir(dp);
}

char	**token_expend_star(char **tokens, int prev_size)
{
	char	**new_tokens;
	int		star_num;
	int		dirs;
	int		i;

	i = 0;
	dirs = star_count_dirs();
	star_num = star_count(tokens);
	new_tokens = malloc(sizeof(char *) * (prev_size + dirs * star_num + 1));
	while (*tokens)
	{
		if (!my_strcmp(*tokens, "*"))
		{
			star_expend_dir(new_tokens, &i);
			tokens++;
			continue;
		}
		new_tokens[i] = ft_strdup(*tokens);
		tokens++;
		i++;
	}
	new_tokens[i] = NULL;
	return (new_tokens);
}

bool	star_exist(char **tokens)
{
	int i;
	int j;
	
	i = 0;
	while (tokens[i])
	{
		j = 0;
		while(tokens[i][j])
		{
			if (tokens[i][j] == '*')
				return (true);
			j++;
		}	
		i++;
	}
	return (false);
}

//create a function that is gonna count the number of tokens
int	count_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

struct token_stream *lexical_analyzer_create(struct scripts *script, struct minishell *minishell)
{
	char **tokens;
	struct token_stream *token_stream;
	t_args args;
	
	args.split_char = " ";
	args.single_word = (char *[]){"||", "|", "&&", "<<", ">>", "<", ">", NULL};
	args.ignore = (char *)"\\";
	args.ign_char_inside = (char *)"\"'";
	tokens = ft_reader(script->input_line, &args);
	script->tokens_num = reader_word_count(script->input_line, &args);
	if (star_exist(tokens) == true)
	{
		tokens = token_expend_star(tokens, script->tokens_num - 1);
		script->tokens_num = count_tokens(tokens);
	}
	// printf("The number of tokens: %d\n", words_count(script->input_line, ';', "\"'") );
	// printer_split(tokens);
	token_stream = ft_create_stack_tkstream(minishell, tokens, script->tokens_num);
	// printer_token(token_stream);
	script->token_stream = token_stream;
	return (token_stream);
}

void minishell_scripts_destroy(struct minishell *minishell) {

}

void lexical_analyzer_destroy(struct token_stream **token_stream) {
	struct token_stream *tmp;

	tmp = *token_stream;
	while (tmp) {
		garbage_collect_token(tmp);
		tmp = tmp->next;
	}
	*token_stream = NULL;
}