/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:11:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/16 16:29:41 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
