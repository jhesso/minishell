/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 05:12:42 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/11 13:38:17 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//These were before we did the expansion and removing quotes,
//Maybe you want to still use this so not deleting!!

// bool	expand_variables(char *str, char **env)
// {
// 	(void)str;
// 	(void)env;
// 	return (true);
// }

// bool	remove_quotes(char *str)
// {
// 	(void)str;
// 	return (true);
// }

bool	append_path(t_tokens *lst_tokens, char **env)
{
	(void)lst_tokens;
	(void)env;
	return (true);
}

/*	parse()
*	parse the saved command line and save into a linked list
*	returns TRUE if parsing was successful, FALSE otherwise
*/
bool	parse(t_minihell *minihell)
{
	//TODO: move list creation here, remove quotes, expand variables, append correct path to command
	if (create_lst_tokens(minihell) == false)
		return (false);
	lst_print(minihell->lst_tokens); //! remove this (debugging purposes)
	if (append_path(minihell->lst_tokens, minihell->env) == false) //TODO: I might be able to simply rip this out from my pipex
		return (false);
	return (true);
}
