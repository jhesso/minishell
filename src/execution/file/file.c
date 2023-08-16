/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:21:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/16 13:09:34 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	open_files()
*	1. Allocate memory for fd arrays
*	2. Open files
*	3. create heredoc if needed
*	4. return true if success
*/
bool	open_files(t_minihell *minihell)
{
	while (minihell->lst_tokens)
	{
		if (!allocate_fds(minihell->lst_tokens))
			return (false);
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	return (true);
}
