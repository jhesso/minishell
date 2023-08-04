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

t_tokens	*lexing(char *command_line)
{
	// t_tokens	*lst_tokens;
	t_lexer		tokens;

	quote_checker(command_line, &tokens);
	tokens.tokens = split_to_tokens(command_line, ' ');
	syntax_checker(tokens.tokens);
	int i = 0;
	while (tokens.tokens[i] != NULL)
	{
		printf("Token:%s\n", tokens.tokens[i]);
		i++;
	}
	// lst_tokens = create_lst_tokens(tokens.tokens);
	// lst_print(lst_tokens);
	// return (lst_tokens);
	return (NULL); //delete this in the end!!!!
}
