/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 05:12:42 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/25 17:57:09 by jhesso           ###   ########.fr       */
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
	if (c == 0 || !ft_strncmp(minihell->tokens[c - 1], "<<\0", 3))
    	minihell->tokens[c] = expand_variables(minihell->tokens[c], minihell->env);
    if (!minihell->tokens[c])
        malloc_error();
    minihell->tokens[c] = remove_quotes(minihell->tokens[c], 0, 0);
    return (ft_strdup(minihell->tokens[c]));
}

/*	parse()
*	parse the saved command line and save into a linked list
*	returns TRUE if parsing was successful, FALSE otherwise
*/
bool	parse(t_minihell *minihell)
{
	if (!create_lst_tokens(minihell))
		return (false);
	return (true);
}
