/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 05:12:42 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/08 05:32:20 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parse()
*	parse the saved command line and save into a linked list
*	returns TRUE if parsing was successful, FALSE otherwise
*/
bool	parse(t_minihell *minihell)
{
	//TODO: move list creation here, remove quotes, expand variables, append correct path to command
	if (remove_quotes(minihell->tokens) == false)
		return (false);
	if (expand_variables(minihell->tokens, minihell->env) == false)
		return (false);
	if (create_lst_tokens(minihell->tokens) == false)
		return (false);
	if (append_path(minihell->lst_tokens, minihell->env) == false)
		return (false);
	return (true);
}
