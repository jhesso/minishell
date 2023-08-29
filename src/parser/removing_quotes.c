/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:42:59 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/29 23:16:33 by dgerguri         ###   ########.fr       */
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

/*	remove_quotes()
*	Removes quotes from string
*	Return value: char * (modified string)
*	Parameters:
*		(char *) str: string to be modified
*		(int) i: index of new string
*		(int) j: index of old string
*/
char	*remove_quotes(char *str, int i, int j, int len)
{
	char	*new_str;
	char	c;

	len = len_without_quotes(str);
	new_str = ft_calloc(sizeof(char), (len + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	while (str[j] && j < len + 1)
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			c = str[j++];
			while (str[j] && str[j] != c)
				new_str[i++] = str[j++];
			if (!str[j] || j == len + 1)
				break ;
		}
		else
			new_str[i++] = str[j++];
	}
	free(str);
	return (new_str);
}
