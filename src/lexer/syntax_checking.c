/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:11:37 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/31 17:59:57 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	syntax_error_messages(int type, char *message)
{
	ft_printf(2, "minishell: syntax error near unexpected token '");
	if (type == 1)
		ft_printf(2, "newline'\n");
	else if (type == 2)
		ft_printf(2, "%s'\n", message);
	error_code = 258;
	return (false);
}

static bool	char_syntax_check_continue(char **tokens, int array)
{
	if (!ft_strrchr("\"\'", tokens[array + 1][0])
		&& ft_strrchr("|<>", tokens[array + 1][0]))
	{
		if (ft_strlen(tokens[array]) == 1 && tokens[array][0] == '<'
			&& tokens[array + 1][0] == '>')
		{
			if (ft_strlen(tokens[array + 1]) == 1)
				return (syntax_error_messages(1, NULL));
			else
				return (syntax_error_messages(2, tokens[array + 1] + 1));
		}
		else if (!tokens[array + 2] || ft_strrchr("|", tokens[array + 1][0]))
			return (syntax_error_messages(2, tokens[array + 1]));
	}
	else if (!ft_strrchr("\"\'", tokens[array][0])
		&& !ft_strrchr("|<>", tokens[array + 1][0]))
	{
		if (ft_strrchr("<>", tokens[array][0]) && ft_strlen(tokens[array]) > 2)
			return (syntax_error_messages(2, tokens[array] + 2));
		else if ((tokens[array][0] == '|' && ft_strlen(tokens[array]) > 1)
			|| tokens[0][0] == '|')
			return (syntax_error_messages(2, tokens[array]));
	}
	return (true);
}

static bool	characters_syntax_check(char **tokens, int array)
{
	if (!tokens[array + 1])
	{
		if (tokens[array][0] == '|')
			return (syntax_error_messages(2, tokens[array]));
		else if (ft_strrchr("><", tokens[array][0])
			&& (ft_strlen(tokens[array]) <= 2
			|| ((ft_strlen(tokens[array]) == 3) && tokens[array][2] == '<')))
			return (syntax_error_messages(1, NULL));
		else
		{
			if (tokens[array][2] == '<')
				return (syntax_error_messages(2, tokens[array] + 3));
			else
				return (syntax_error_messages(2, tokens[array] + 2));
		}
	}
	else if (!char_syntax_check_continue(tokens, array))
		return (false);
	return (true);
}

bool	syntax_checker(char **tokens)
{
	int	array;
	int	i;

	array = 0;
	i = 0;
	while (tokens[array])
	{
		if (tokens[array][i] && ft_strrchr("|><", tokens[array][i])
			&& !ft_strrchr("\'\"", tokens[array][i]))
			if (!characters_syntax_check(tokens, array))
				return (false);
		array++;
	}
	return (true);
}
