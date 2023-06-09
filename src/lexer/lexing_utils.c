/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:11:25 by dgerguri          #+#    #+#             */
/*   Updated: 2023/06/25 19:27:11 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_checker(char *command_line, t_lexer *tokens)
{
	int	i;

	i = 0;
	tokens->double_quote = 0;
	tokens->single_quote = 0;
	while (command_line[i])
	{
		if (command_line[i] == '\"')
			tokens->double_quote++;
		else if (command_line[i] == '\'')
			tokens->single_quote++;
		else if ((ft_strrchr("\\;()", command_line[i]))
			&& tokens->single_quote % 2 != 1 && tokens->double_quote % 2 != 1) // this only does it if it is outside the quotes bc if we do quotes echo it should echo it!
		{
			ft_putstr_fd("Minishell: Syntax Error: Semicolon, Backslash, or Bracket!\n", 1);
			exit(1); // It shouldnt exit!!!!!//check this later and move it somwhere else! Will probably have to free stuff also!
		}
		i++;
	}
	if (tokens->double_quote % 2 != 0 || tokens->single_quote % 2 != 0)
	{
		ft_putstr_fd("Minishell: Syntax Error: Open Quotes!\n", 1);
		exit(1); // It shouldnt exit!!!!!//check this later and move it somwhere else! Will probably have to free stuff also!
	}
}
