/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 04:29:45 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/25 19:10:20 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! this is only for testing for now
// void	close_files(t_minihell *minihell)
// {
// 	while (minihell->lst_tokens)
// 	{
// 		if (minihell->lst_tokens->fd_in > 0)
// 			close(minihell->lst_tokens->fd_in);
// 		if (minihell->lst_tokens->fd_out > 0)
// 			close(minihell->lst_tokens->fd_out);
// 		close(minihell->pipe_fds[0]);
// 		close(minihell->pipe_fds[1]);
// 		minihell->lst_tokens = minihell->lst_tokens->next;
// 	}
// }
