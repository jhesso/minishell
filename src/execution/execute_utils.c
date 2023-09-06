/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:46:58 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 20:53:33 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	redirect_io()
*	Redirects input and output to either specified files or to a pipe
*	Close unused file descriptors
*/
void	redirect_io(t_cmds *cmd, int **pipe_fds, int nb_cmd)
{
	if (cmd->fd_in > 0 && !check_builtin(cmd->command))
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			dup_error();
	}
	else if (nb_cmd)
	{
		if (dup2(pipe_fds[nb_cmd - 1][0], STDIN_FILENO) == -1)
			dup_error();
	}
	if (cmd->fd_out > 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			dup_error();
	}
	else if (cmd->next)
	{
		if (dup2(pipe_fds[nb_cmd][1], STDOUT_FILENO) == -1)
			dup_error();
	}
}

void	solo_builtin(t_minihell *mini, int i)
{
	int	stdout_cpy;

	stdout_cpy = -2;
	if (mini->cmds->fd_out > 0)
		stdout_cpy = dup(STDOUT_FILENO);
	redirect_io(mini->cmds, mini->pipe_fds, i);
	close_pipes(mini);
	execute_builtin(mini, check_builtin(mini->cmds->command));
	if (stdout_cpy != -2)
		dup2(stdout_cpy, STDOUT_FILENO);
}
