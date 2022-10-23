/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:23:20 by frmessin          #+#    #+#             */
/*   Updated: 2022/10/22 20:42:50 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>

typedef struct s_args
{
	char	*split_char;
	char	**single_word;
	char	*ignore;
	char	*ign_char_inside;
}	t_args;

/*	WORD COUNT	*/
int		found_split_char(int i, bool *word);
int		found_word(bool *word, int i, int *word_count);
int		found_char_to_ignore(int *word_count, int i, char *string, bool *word);
int		reader_word_count(char *string, t_args *args);
int		jump_char_inside(char *string, char *special,
			int *word_count, bool *word);
int		single_word_strchr(char **single_word, char *string);
char	*create_the_word(char *string, int n);
int		check_for_word(char *string, t_args *args);

#endif

/*
	It is based on a struct called s_args which takes 4
	params:

	SPLIT_CHAR:  which is a string of value that should
		split the words (like spaces for example);
	SINGLE_WORD:  which is a string of char that if
		read should create a single word ex: |echo|
		should return => [|][echo][|];
	IGNORE:  which contain special char that should be
		"ignored" by the split if at the previous index
		ex: \\ in bash;
	IGNORE_CHAR_INSIDE:  special char that initialize a string
		that should be ignored by the function split
		ex: "ehci uwhe" should return a single word;
*/