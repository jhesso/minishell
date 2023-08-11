/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:11:25 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/11 18:03:06 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	char_checker(char *command_line, t_minihell *command, int i)
{
	command->double_quote = 0;
	command->single_quote = 0;
	while (command_line[i])
	{
		if (command_line[i] == '\"')
			command->double_quote++;
		else if (command_line[i] == '\'')
			command->single_quote++;
		else if ((ft_strrchr("\\;()", command_line[i]))
			&& command->single_quote % 2 != 1 && command->double_quote % 2 != 1)
		{
			ft_putstr_fd("Minishell: Syntax Error:\
 Semicolon, Backslash, or Bracket!\n", 1);
			return (false);
		}
		i++;
	}
	if (command->double_quote % 2 != 0 || command->single_quote % 2 != 0)
	{
		ft_putstr_fd("Minishell: Syntax Error: Open Quotes!\n", 1);
		return (false);
	}
	return (true);
}

int	quotes(char const *s, int i)
{
	char	c;

	c = s[i];
	i += 1;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
