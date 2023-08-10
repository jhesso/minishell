/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:42:59 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/10 21:44:13 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_without_quotes(char *str)
{
	int 	len;
	int		flag;
	char	c;

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
				break;
			flag++;
		}
		len++;
	}
	printf("%d\n", len);
	return (len - flag);
}

char *remove_quotes(char *str)
{
	int len;
	int i;
	int j;
	char	c;
	char *new_str;

	len = len_without_quotes(str);
	i = 0;
	j = 0;
	new_str = ft_calloc(sizeof(char), (len + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	while (str[j] && j < len)
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			c = str[j++];
			while (str[j] && str[j] != c)
				new_str[i++] = str[j++];
			if (str[j] || j == len)
				break ;
		}
		new_str[i++] = str[j++];
	}
	free(str);
	return (new_str);
}
