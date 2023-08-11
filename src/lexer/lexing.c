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

bool	lexing(t_minihell *command, char *command_line)
{
	if (char_checker(command_line, command, 0) == false)
		return (false);
	if ((command->tokens = tokenize_cmd(command_line, ' ')) == NULL)
		return (false);
	//We already have a function that frees the allocated strings in case they fail!for some reason!
	//So, we dont have to free anything in case this returns NULL!
	// The free function will be located at the lexing_utils!
	if (syntax_checker(command->tokens) == false)
	{
		//dont forget to freee!!!
		return (false);
	}
	// print_string_arr(command->tokens); //* this does the same thing as the previous while loop (inisde my libft)
	return (true);
}
