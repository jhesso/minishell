/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/11 19:09:51 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**tokenize_cmd(char const *s, char c)
{
	char			**ret;
	unsigned int	i;
	unsigned int	row;
	unsigned int	word_count;

	if (s == NULL)
		return (NULL);
	word_count = get_amount_of_words(s, c);
	ret = malloc(sizeof(char *) * (word_count + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	row = -1;
	while (++row < word_count)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c)
			ret[row] = ft_substr(s, i, get_word_len(s, c, i));
		if (ret[row] == NULL)
			return (free_str_arr(ret));
		i = i + get_word_len(s, c, i);
	}
	ret[row] = NULL;
	return (ret);
}

bool	lexing(t_minihell *command, char *command_line)
{
	if (!char_checker(command_line, command, 0))
		return (false);
	command->tokens = tokenize_cmd(command_line, ' ');
	if (!command->tokens)
	{
		free(command_line);
		return (false);
	}
	free(command_line);
	if (!syntax_checker(command->tokens))
	{
		free_str_arr(command->tokens);
		return (false);
	}
	return (true);
}
