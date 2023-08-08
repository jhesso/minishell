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

void	lexing(t_minihell *command, char *command_line) //! change return type to bool if we need to return something incase of failure
{
	quote_checker(command_line, command);
	command->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(command->tokens);
	// print_string_arr(command->tokens); //* this does the same thing as the previous while loop (inisde my libft)
}
