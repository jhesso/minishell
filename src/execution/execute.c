/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 20:22:10 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	redirect_io()
*	Redirects input and output to either specified files or to a pipe
*	Close unused file descriptors
*/
static void	redirect_io(t_tokens *cmd, int **pipe_fds, int nb_cmd)
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

/*	child()
*	Child process executes the command and/or builtin function
*	redirects input and output to either specified files or to a pipe
*/
static void	child(t_tokens *cmd, t_minihell *mini, int not_first_cmd)
{
	if (!cmd->command)
		exit(g_global.error_code);
	redirect_io(cmd, mini->pipe_fds, not_first_cmd);
	close(mini->pipe_fds[not_first_cmd][0]);
	if (check_builtin(cmd->command))
	{
		execute_builtin(mini, check_builtin(cmd->command));
		exit(g_global.error_code);
	}
	if (execve(cmd->command, cmd->argv, mini->env) == -1)
	{
		perror(strerror(errno));
		g_global.error_code = errno;
	}
}

/*	parent()
*	Parent process waits for all child processes to finish
*	Also saves the exit status of the last command (for $?)
*/
static void	parent(t_minihell *mini)
{
	int			status;
	int			i;
	t_tokens	*tmp;

	i = 0;
	close_pipes(mini);
	tmp = mini->cmds;
	while (i < mini->nb_cmds)
	{
		if (mini->pids[i] != -2)
			waitpid(mini->pids[i], &status, 0);
		if (!check_builtin(mini->cmds->command) && WIFEXITED(status))
			g_global.error_code = WEXITSTATUS(status);
		i++;
		mini->cmds = mini->cmds->next;
	}
}

static void	solo_builtin(t_minihell *mini, int i)
{
	int	stdout_cpy;

	if (mini->cmds->fd_out > 0)
		stdout_cpy = dup(STDOUT_FILENO);
	redirect_io(mini->cmds, mini->pipe_fds, i);
	close_pipes(mini);
	execute_builtin(mini, check_builtin(mini->cmds->command));
	dup2(stdout_cpy, STDOUT_FILENO);
}

/*	execute()
*	Execute the command line
*	g_global.error_code is set to the exit status of the last command
*	Returns TRUE if execution was successful, FALSE otherwise
*/
void	execute(t_minihell *mini)
{
	t_tokens	*head;
	int			i;

	prepare_execution(mini);
	head = mini->cmds;
	i = 0;
	while (mini->cmds)
	{
		open_files(mini, i, false, false);
		if (pipe(mini->pipe_fds[i]) == -1)
		{
			perror(strerror(errno));
			g_global.error_code = errno;
			break ;
		}
		if (mini->cmds->fd_in == -1 || mini->cmds->fd_out == -1)
		{
			free(mini->cmds->command);
			mini->cmds->command = NULL;
		}
		if (check_builtin(mini->cmds->command) && mini->nb_cmds == 1)
			solo_builtin(mini, i);
		else
			mini->pids[i] = fork();
		if (mini->pids[i] == -1)
		{
			perror(strerror(errno));
			g_global.error_code = errno;
			break ;
		}
		else if (mini->pids[i] == 0)
			child(mini->cmds, mini, i);
		else
			close(mini->pipe_fds[i][1]);
		i++;
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = head;
	parent(mini);
}
