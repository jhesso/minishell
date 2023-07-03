/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/06/29 17:13:15 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count_redirections(char **tokens, int)

// t_commands	*command_type(char **tokens)
// {
// 	int array;
// 	int i;

// 	array = 0;
// 	i = 0;
// 	while (tokens[array])
// 	{
// 		if (ft_strrchr("<", tokens[array][i]))
// 	}
// }

void	lexing(char *command_line, t_lexer *tokens)
{
	t_commands *cmd;

	quote_checker(command_line, tokens);
	tokens->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(tokens->tokens);
	// cmd = command_type(tokens->tokens);   //jhesso I have no idea what to name it :(


	//This is to test the tokens!
	// int i = 0;
	// while (tokens->tokens[i] != NULL)
	// {
	// 	printf("%s\n", tokens->tokens[i]);
	// 	i++;
	// }
}
