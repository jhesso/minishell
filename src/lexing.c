/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/06/19 18:36:51 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_words_with_characters(char const *s, char c, int amount)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while(s[i]!= '\0')
	{
		if (ft_strrchr("|;><", s[i]))
		{
			if (i == 0 && s[i + 1] == c)
			{
				amount = amount + 0;
				flag = 1;
			}
			if (s[i - 1] == c)
				amount = amount + 0;
			if (s[i + 1] != c && s[i - 1] != '\0' && s[i - 1] != c)
				amount = amount + 1;
			if (s[i + 1] != '\0' && s[i + 1] == c && s[i - 1] != '\0' && s[i - 1] == c)
				amount = amount + 0;
			else if (!ft_strrchr("|;><", s[i + 1]) && flag == 0)
				amount++;
		}
		i++;
	}
	return (amount);
}

static int	get_amount_of_words(char const *s, char c)
{
	int	amount;
	int	i;

	amount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			amount++;
			while (s[i] != c && s[i + 1] != '\0')
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
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	i = start;
	while (s[i] == c)
		i++;
	len = 0;
	if (ft_strrchr("|;><", s[i]))
		return (1);
	while(s[i]!= '\0' && s[i] != c && !ft_strrchr("|;><", s[i]))
	{
		i++;
		len++;
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
	tokens->tokens = ft_split_(command_line, ' ');
	int i = 0;
	while (tokens->tokens[i] != NULL)
	{
		printf("%s\n", tokens->tokens[i]);
		i++;
	}
}
