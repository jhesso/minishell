/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/06 17:53:511 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*lexing(t_minihell *command, char *command_line)
{
	// t_tokens	*lst_tokens;

	quote_checker(command_line, command);
	command->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(command->tokens);
	int i = 0;
	while (command->tokens[i] != NULL)
	{
		printf("Token:%s\n", command->tokens[i]);
		i++;
	}
	// lst_tokens = create_lst_tokens(command->tokens);
	// lst_print(lst_tokens);
	// return (lst_tokens);
	return (NULL); //delete this in the end!!!!
}
