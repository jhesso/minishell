/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:42:59 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/12 15:15:49 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	len_without_quotes()
*	Calculates the length of the string without quotes
*	Return value: int (length of the string without quotes)
*	Parameters:
*		(char *) str: string to be calculated
*/
static int	len_without_quotes(char *str)
{
	char	c;
	int		len;
	int		flag;

	len = 0;
	flag = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			flag++;
			c = str[len++];
			while (str[len] && str[len] != c)
				len++;
			if (str[len] == '\0')
				break ;
			flag++;
		}
		len++;
	}
	return (len - flag);
}

static char	*remove_quotes_continues(char *new_str, char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (str[j] && (size_t)j <= ft_strlen(str))
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			c = str[j++];
			while (str[j] && str[j] != c)
				new_str[i++] = str[j++];
			if (!str[j] || (size_t)j == ft_strlen(str))
				break ;
		}
		else
			new_str[i++] = str[j++];
		if (str[j] && str[j] == c)
			j++;
	}
	return (new_str);
}

/*	remove_quotes()
*	Removes quotes from string
*	Return value: char * (modified string)
*	Parameters:
*		(char *) str: string to be modified
*		(int) i: index of new string
*		(int) j: index of old string
*/
char	*remove_quotes(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_calloc(sizeof(char), (len_without_quotes(str) + 1));
	if (!new_str)
		malloc_error();
	if (!*str)
	{
		free(str);
		return (new_str);
	}
	new_str = remove_quotes_continues(new_str, str);
	free(str);
	return (new_str);
}
