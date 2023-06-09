/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:11:37 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/05 17:32:11 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void syntax_error_messages(int type, char *message)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	if (type == 1)
	{
		ft_putstr_fd("newline'\n", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("'\n", 2);
	}
	// if (type == 2 || type == 1)
	// 	error code = 258; will have to figure it out how we do this!! when we do $?

	// exit(1);

}



static void	characters_syntax_check(char **tokens, int array)
{
		if (tokens[array + 1] == NULL)
		{
			if (tokens[array][0] == '|')
				syntax_error_messages(2, tokens[array]);
			else if (ft_strrchr("><", tokens[array][0]) && (ft_strlen(tokens[array]) <= 2
				|| ((ft_strlen(tokens[array]) == 3) && tokens[array][2] == '<')))
				syntax_error_messages(1, NULL);
			else
			{
				if (tokens[array][2] == '<')
					syntax_error_messages(2, tokens[array] + 3);
				else
					syntax_error_messages(2, tokens[array] + 2);
			}
		}
		else if (!ft_strrchr("\"\'", tokens[array + 1][0]) && ft_strrchr("|<>", tokens[array + 1][0]))
		{
			if (ft_strlen(tokens[array]) == 1 && tokens[array][0] == '<' && tokens[array + 1][0] == '>')
				{
					if (ft_strlen(tokens[array + 1]) == 1)
						syntax_error_messages(1, NULL);
					else
						syntax_error_messages(2, tokens[array + 1] + 1);
				}
			else
				syntax_error_messages(2, tokens[array + 1]);
		}
		else if (!ft_strrchr("\"\'", tokens[array][0]) && !ft_strrchr("|<>", tokens[array + 1][0]))
		{
			if (ft_strrchr("<>", tokens[array][0]) && ft_strlen(tokens[array]) > 2)
				syntax_error_messages(2, tokens[array] + 2);
			else if ((tokens[array][0] == '|' && ft_strlen(tokens[array]) > 1) || tokens[0][0] == '|')
				syntax_error_messages(2, tokens[array]);
		}

}

void	syntax_checker(char **tokens)
{
	int array;
	int i;

	array = 0;
	i = 0;
	while (tokens[array] != NULL)
	{

		if (tokens[array][i] && ft_strrchr("|><", tokens[array][i])
			&& !ft_strrchr("\'\"", tokens[array][i]))
				characters_syntax_check(tokens, array);
		array++;
	}
}
