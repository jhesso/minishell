/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:59:01 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/05 12:47:55 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	open_pipe(t_tokens *tmp)
// {
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		global.error_code = errno;
// 	}
// 	tmp->fd_out = fd[1];
// 	tmp->next->fd_in = fd[0];
// }

// void	open_pipes(t_tokens *lst_tokens)
// {
// 	t_tokens	*tmp;

// 	tmp = lst_tokens;
// 	while (tmp)
// 	{
// 		if (tmp->next != NULL && tmp->fd_out <= 0)
// 			open_pipe(tmp);
// 		tmp = tmp->next;
// 	}
// }
