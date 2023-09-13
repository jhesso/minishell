/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:11:37 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/13 19:44:53 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	syntax_error_messages(t_minihell *mini, int type, char *message)
{
	ft_printf(2, "minishell: syntax error near unexpected token '");
	if (type == 1)
		ft_printf(2, "newline'\n");
	else if (type == 2)
	{
		if (!message[1] || !message[2])
			ft_printf(2, "%s'\n", message);
		else
			ft_printf(2, "%s'\n", "<<<");
	}
	else if (type == 3)
	{
		if (!message[1])
			ft_printf(2, "%s'\n", message);
		else
			ft_printf(2, "%s'\n", ">>");
	}
	else if (type == 4)
		ft_printf(2, "%s'\n", message);
	mini->error_code = 258;
	return (false);
}

static bool	char_syntax_check_cont(t_minihell *mini, char **tokens, int array)
{
	if (tokens[array + 1][0] == '|')
		return (syntax_error_messages(mini, 2, tokens[array + 1]));
	if (ft_strrchr("<>", tokens[array + 1][0]) || ft_strlen(tokens[array]) > 2)
	{
		if (tokens[array][0] == '<' && !ft_strrchr("><", tokens[array + 1][0])
			&& ft_strlen(tokens[array]) == 3)
			return (syntax_error_messages(mini, 2, tokens[array]));
		else if (tokens[array][0] == '<' && ft_strlen(tokens[array]) > 3)
			return (syntax_error_messages(mini, 2, tokens[array] + 3));
		else if (tokens[array][0] == '>' && ft_strlen(tokens[array]) > 2)
			return (syntax_error_messages(mini, 3, tokens[array] + 2));
		else if (tokens[array + 1][0] == '<')
			return (syntax_error_messages(mini, 2, tokens[array + 1]));
		else if (tokens[array + 1][0] == '>')
			return (syntax_error_messages(mini, 3, tokens[array + 1]));
	}
	return (true);
}

static bool	characters_syntax_check(t_minihell *mini, char **tokens, int array)
{
	if (!tokens[array + 1])
	{
		if (tokens[array][0] == '<')
		{
			if (ft_strlen(tokens[array]) > 3)
				return (syntax_error_messages(mini, 2, tokens[array] + 3));
			else
				return (syntax_error_messages(mini, 1, NULL));
		}
		else if (tokens[array][0] == '>')
		{
			if (ft_strlen(tokens[array]) > 2)
				return (syntax_error_messages(mini, 3, tokens[array] + 2));
			else
				return (syntax_error_messages(mini, 1, NULL));
		}
	}
	else if (!char_syntax_check_cont(mini, tokens, array))
		return (false);
	return (true);
}

bool	syntax_checker(t_minihell *minihell, char **tokens)
{
	int	array;

	array = 0;
	while (tokens[array])
	{
		if (tokens[array][0] == '|'
		&& (array == 0 || !tokens[array + 1] || ft_strlen(tokens[array]) > 1))
		{
			if (ft_strlen(tokens[array]) > 1)
				return (syntax_error_messages(minihell, 4, "||"));
			else
				return (syntax_error_messages(minihell, 4, "|"));
		}
		else if (ft_strrchr("><", tokens[array][0]))
			if (!characters_syntax_check(minihell, tokens, array))
				return (false);
		array++;
	}
	return (true);
}
