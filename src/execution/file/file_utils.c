/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:11:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/16 13:16:14 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*	allocate_fds()
*	allocate memory for the fd arrays
*	Returns true if successful, false if not
*/
bool	allocate_fds(t_tokens *node)
{
	int	input;
	int	output;

	input = count_strings(node->in) + count_strings(node->heredoc);
	output = count_strings(node->out) + count_strings(node->out_app);
	node->fd_in = malloc(sizeof(int) * (input + 1));

}
