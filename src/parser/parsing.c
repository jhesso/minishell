/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 05:12:42 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/08 12:58:13 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_variables(char *str, char **env);

bool	remove_quotes(char *str);

/*	parse()
*	parse the saved command line and save into a linked list
*	returns TRUE if parsing was successful, FALSE otherwise
*/
bool	parse(t_minihell *minihell)
{
	//TODO: move list creation here, remove quotes, expand variables, append correct path to command
	int	i;

	i = 0;
	while (minihell->tokens[i] != NULL)
	{
		if (remove_quotes(minihell->tokens[i]) == false)
			return (false);
		if (expand_variables(minihell->tokens[i], minihell->env) == false)
			return (false);
	}
	if (create_lst_tokens(minihell->tokens) == false)
		return (false);
	if (append_path(minihell->lst_tokens, minihell->env) == false) //TODO: I might be able to simply rip this out from my pipex
		return (false);
	return (true);
}
