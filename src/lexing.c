/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/06/25 19:50:30 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
