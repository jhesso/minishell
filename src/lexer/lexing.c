/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/04 12:01:27 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count_redirections(char **tokens, int)
// {
// 	while ()
// }
void	mem_allocation(char **tokens, int start)
{
	while (tokens[start])
	{
		count
	}
}

t_commands	*command_type(char **tokens)
{
	t_commands	*commands; //change the name
	int			array;
	int			i;

	commands = NULL;
	array = 0;
	i = 0;
	while (tokens[array])
	{
		while (tokens[array][i] != '|')
		{
			mem_allocation(tokens, array);
		}
		array++;
		commands = commands->next;
	}
}

void	lexing(char *command_line, t_lexer *tokens)
{
	t_commands *cmd;

	quote_checker(command_line, tokens);
	tokens->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(tokens->tokens);
	cmd = command_type(tokens->tokens);   //jhesso I have no idea what to name it :(


	//This is to test the tokens!
	// int i = 0;
	// while (tokens->tokens[i] != NULL)
	// {
	// 	printf("%s\n", tokens->tokens[i]);
	// 	i++;
	// }
}
