/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 17:59:32 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_io(t_tokens *cmd, int *pipe_fds, int *old_fds)
{
	if (cmd->fd_in > 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	else
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
	}
	close(old_fds[0]);
	if (cmd->fd_out > 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(pipe_fds[1], STDOUT_FILENO);
	else
	{
		dup2(STDOUT_FILENO, old_fds[1]);
		close(old_fds[1]);
	}
	close(pipe_fds[1]);
}

static void	child(t_tokens *cmd, t_minihell *mini)
{
	int	builtin;

	if (!cmd->command)
		return ;
	redirect_io(cmd, mini->pipe_fds, mini->old_fds);
	builtin = check_builtin(cmd->command);
	if (builtin > 0)
		execute_builtin(mini, builtin);
	else if (execve(cmd->command, cmd->argv, mini->env) == -1)
	{
		perror(strerror(errno));
		error_code = errno;
	}
}
static void	parent_io(t_tokens *cmd, int *pipe_fds, int *old_fds)
{
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	if (cmd->fd_out > 0)
		close(cmd->fd_out);
	if (cmd->next)
	{
		old_fds[0] = pipe_fds[0];
		old_fds[1] = pipe_fds[1];
		close(pipe_fds[1]);
		close(pipe_fds[0]);
	}
	else
	{
		close(old_fds[0]);
		close(old_fds[1]);
	}
}

static void	parent(t_tokens *cmd, t_minihell *mini, int i)
{
	int		status;

	parent_io(cmd, mini->pipe_fds, mini->old_fds);
	waitpid(mini->pids[i], &status, 0);
	if (WIFEXITED(status))
		error_code = WEXITSTATUS(status);
}

bool	execute(t_minihell *minihell)
{ //! Realized a potential problem with heredoc: if more than one command has heredoc as input, only the last commands heredoc will be kept
	t_tokens	*head;
	int			i;

	// print_string_arr(minihell->tokens);
	// lst_print(minihell->lst_tokens);
	prepare_execution(minihell);
	head = minihell->lst_tokens;
	i = 0;
	while (minihell->lst_tokens)
	{
		if (pipe(minihell->pipe_fds) == -1)
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		minihell->pids[i] = fork();
		if (minihell->pids[i] == -1)
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		else if (minihell->pids[i] == 0)
			child(minihell->lst_tokens, minihell);
		else
			parent(minihell->lst_tokens, minihell, i);
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	//TODO: unlink heredoc
	minihell->lst_tokens = head;
	return (true);
}
