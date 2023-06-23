/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/06/23 15:41:40 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int quotes(char const *s, int i)
{
	char	c;

	c = s[i];
	i += 1;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	get_words_with_characters(char const *s, char c, int amount)
{
	int	i;

	i = 0;
	if (s[i] && ft_strrchr("|><", s[i]))
	{
		i++;
		while (s[i] && s[i] == s[i - 1])
			i++;
	}
	else if (s[i] && ft_strrchr("\'\"", s[i]))
	{
		i = quotes(s, i);
		i++;
	}
	else if (s[i] && !ft_strrchr("|><", s[i]) && s[i] != c && !ft_strrchr("\"\'", s[i]))
		while (s[i] && !ft_strrchr("|><", s[i]) && s[i] != c && !ft_strrchr("\"\'", s[i]))
			i++;
	// printf("Amount: %d %d %c\n", amount, i, s[i]);
	while (s[i])
	{
		if (s[i] && s[i] != c && !ft_strrchr("|><", s[i]) && !ft_strrchr("\'\"", s[i]))
		{
			if (s[i] && s[i - 1] != c && !ft_strrchr("\'\"", s[i - 1]))
				amount++;
			while (s[i] && s[i] != c && !ft_strrchr("|><", s[i]))
				i++;
		}
		if (s[i] == c)
			i++;
		if (s[i] && ft_strrchr("|><", s[i]))
		{
			if (s[i - 1] != c)
				amount++;
			i++;
			while (s[i] && s[i] == s[i - 1])
				i++;
		}
		if (s[i] && ft_strrchr("\'\"", s[i]))
		{
			i = quotes(s, i);
			i++;
		}
	}
	return (amount);
}

static int	get_amount_of_words(char const *s, char c)
{
	int	amount;
	int	i;

	amount = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			amount++;
			if (s[i] && ft_strrchr("\'\"", s[i]))
				i = quotes(s, i);
			while (s[i] && s[i] != c && s[i + 1] != '\0' && !ft_strrchr("\'\"", s[i]) && !ft_strrchr("\'\"", s[i + 1]))
				i++;
		}
		i++;
	}
	amount = get_words_with_characters(s, c, amount);
	return (amount);
}


static	int	get_word_len(char const *s, char c, int start)
{
	int	i;
	int	len;

	i = start;
	while (s[i] == c)
		i++;
	len = 0;
	if (s[i] && ft_strrchr("\'\"", s[i]))
	{
		len = i;
		i = quotes(s, i);
		len = i - len + 1;
	}
	else if (s[i] && s[i] != c && !ft_strrchr("|><", s[i]))
	{
		while (s[i] && s[i] != c && !ft_strrchr("|><\"\'", s[i++]))
			len++;
	}
	else if (s[i] && s[i] != c && ft_strrchr("|><", s[i++]))
	{
		len++;
		while (s[i] && s[i] == s[i - 1])
		{
				len++;
				i++;
		}
	}
	return (len);
}

static char	**free_allocated_strings(char **ret, int row)
{
	while (row >= 0)
		free(ret[row--]);
	free(ret);
	return (NULL);
}

char	**ft_split_(char const *s, char c)
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
			return (free_allocated_strings(ret, row));
		i = i + get_word_len(s, c, i);
	}
	ret[row] = NULL;
	return (ret);
}

void	lexing(char *command_line, t_lexer *tokens)
{
	check_quotes(command_line, tokens);
	tokens->tokens = ft_split_(command_line, ' ');
	int i = 0;
	while (tokens->tokens[i] != NULL)
	{
		printf("%s\n", tokens->tokens[i]);
		i++;
	}
}
