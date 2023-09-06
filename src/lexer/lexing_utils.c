/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:11:25 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/06 19:14:11 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes(char const *s, int i)
{
	char	c;

	c = s[i];
	i += 1;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

bool	char_checker(char *command_line, int i, int flag)
{
	while (command_line[i])
	{
		if (command_line[i] == '\"' || command_line[i] == '\'')
		{
			flag = 1;
			i = quotes(command_line, i);
		}
		else if ((ft_strrchr("\\;()", command_line[i])))
		{
			ft_printf(2, "Minishell: Syntax Error:\
 Semicolon, Backslash, or Bracket!\n");
			return (false);
		}
		if (!command_line[i] && flag == 1)
		{
			ft_printf(2, "Minishell: Syntax Error: Open Quotes!\n");
			return (false);
		}
		else
			flag = 0;
		i++;
	}
	return (true);
}
