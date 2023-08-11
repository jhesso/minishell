/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:11:25 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/11 16:31:41 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	character_checker(char *command_line, t_minihell *command, int i)
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

char	**free_allocated_strings(char **ret, int row)
{
	while (row >= 0)
		free(ret[row--]);
	free(ret);
	return (NULL);
}
