/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:28:05 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/11 17:57:23 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_patterns(char const *s, char c, int *i, int amount)
{
	if (s[*i] && s[*i] != c && !ft_strrchr("|><", s[*i])
	&& !ft_strrchr("\'\"", s[*i]))
	{
		if (s[*i] && s[*i - 1] != c && !ft_strrchr("\'\"", s[*i - 1]))
			amount++;
		while (s[*i] && s[*i] != c && !ft_strrchr("\"\'|><", s[*i]))
			i++;
	}
	if (s[*i] == c)
		i++;
	if (s[*i] && ft_strrchr("|><", s[*i]))
	{
		if (s[*i - 1] != c)
			amount++;
		i++;
		while (s[*i] && s[*i] == s[*i - 1])
			i++;
	}
	if (s[*i] && ft_strrchr("\'\"", s[*i]))
	{
		if (ft_strrchr("|><", s[*i - 1]))
			amount++;
		*i = quotes(s, *i) + 1;
	}
	return (amount);
}

static int	handle_character_patterns(char const *s, char c, int amount)
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
	while (s[i])
	{
		amount = handle_patterns(s, c, &i, amount);
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
			while (s[i] && s[i] != c && s[i + 1] != '\0')
				i++;
		}
		i++;
	}
	amount = handle_character_patterns(s, c, amount);
	return (amount);
}


static	int	get_word_len(char const *s, char c, int start)
{
	int	len;
	int	i;

	len = 0;
	i = start;
	while (s[i] == c)
		i++;
	if (s[i] && s[i] != c && !ft_strrchr("|><", s[i]))
	{
		while (s[i] && s[i] != c && !ft_strrchr("|><", s[i]))
		{
			if (s[i] && ft_strrchr("\'\"", s[i]) && s[i] != c && !ft_strrchr("|><", s[i]))
			{
				i = quotes(s, i) + 1;
				len = i - start;
			}
			while (s[i] && s[i] != c && !ft_strrchr("\'\"|><", s[i]))
			{
				len++;
				i++;
			}
		}
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

char	**tokenize_cmd(char const *s, char c)
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
			return (free_str_arr(ret, row));
		i = i + get_word_len(s, c, i);
	}
	ret[row] = NULL;
	return (ret);
}
