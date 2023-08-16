/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:11:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/16 17:20:35 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*	allocate_fds()
*	allocate memory for the fd arrays
*	Returns true if successful, false if not
*/
void	allocate_fds(t_tokens *node)
{
	int	input;
	int	output;

	input = count_strings(node->in) + count_strings(node->heredoc);
	output = count_strings(node->out) + count_strings(node->out_app);
	node->fd_in = malloc(sizeof(int) * input);
	node->fd_out = malloc(sizeof(int) * output);
	if (!node->fd_in || !node->fd_out)
		malloc_error();
}
