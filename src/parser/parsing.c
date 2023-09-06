/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 05:12:42 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 19:20:03 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	parse_str()
*	expand environment variables and remove extra quotes
*	Return value: char * (modified string)
*	Parameters:
*		int c: index of the string we are modifying
*		t_minihell *minihell: our minihell struct containing the strings to be modified
*/
char    *parse_str(int c, t_minihell *minihell)
{
	if (c == 0 || ft_strncmp(minihell->tokens[c - 1], "<<\0", 3))
		minihell->tokens[c] = expand_variables(minihell->tokens[c], minihell->env);
	if (!minihell->tokens[c])
		malloc_error();
	if (!minihell->tokens[c][0])
		return (NULL);
	if (c != 0 && (!ft_strncmp(minihell->tokens[c - 1], "<\0", 2) ||
		!ft_strncmp(minihell->tokens[c - 1], "<<\0", 3) ||
		!ft_strncmp(minihell->tokens[c - 1], ">\0", 2) ||
		!ft_strncmp(minihell->tokens[c - 1], ">>\0", 3)))
		return (NULL);
	return (ft_strdup(minihell->tokens[c]));
}

/*	parse()
*	parse the saved command line and save into a linked list
*	returns TRUE if parsing was successful, FALSE otherwise
*/
bool	parse(t_minihell *minihell)
{
	if (!create_cmds(minihell))
		return (false);
	return (true);
}
