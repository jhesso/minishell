/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 21:03:38 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_io(t_tokens *cmd, int *pipe_fds, int not_first_cmd)
{
	if (cmd->fd_in > 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(pipe_fds[0]);
	}
	else if (not_first_cmd)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
	}
	if (cmd->fd_out > 0)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else if (cmd->next)
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
	}
	if (!cmd->next)
		close(pipe_fds[1]);
	if (!not_first_cmd)
		close(pipe_fds[0]);
}

static void	child(t_tokens *cmd, t_minihell *mini, int not_first_cmd)
{
	int	builtin;

	if (!cmd->command)
		return ;
	redirect_io(cmd, mini->pipe_fds, not_first_cmd);
	builtin = check_builtin(cmd->command);
	if (builtin > 0)
		execute_builtin(mini, builtin);
	else if (execve(cmd->command, cmd->argv, mini->env) == -1)
	{
		perror(strerror(errno));
		error_code = errno;
	}
}

static void	parent_io(int *pipe_fds)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

static void	parent(t_minihell *mini)
{
	int		status;
	int		i;

	i = 0;
	while(i < mini->nb_cmds)
		waitpid(mini->pids[i++], &status, 0);
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
			child(minihell->lst_tokens, minihell, i);
		else
			parent_io(minihell->pipe_fds);
		if (minihell->pids[i] == 0)
			exit(error_code);
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	parent(minihell);
	//TODO: unlink heredoc
	minihell->lst_tokens = head;
	return (true);
}
