/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/15 15:02:06 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	child()
*	Child process executes the command and/or builtin function
*	redirects input and output to either specified files or to a pipe
*/
static void	child(t_cmds *cmd, t_minihell *mini, int not_first_cmd)
{
	if (!cmd->command)
	{
		close_pipes(mini);
		exit(mini->error_code);
	}
	redirect_io(cmd, mini->pipe_fds, not_first_cmd);
	close(mini->pipe_fds[not_first_cmd][0]);
	if (check_builtin(cmd->command))
	{
		execute_builtin(mini, check_builtin(cmd->command));
		exit(mini->error_code);
	}
	if (execve(cmd->command, cmd->argv, mini->env) == -1)
	{
		perror(strerror(errno));
		mini->error_code = errno;
	}
}

/*	parent()
*	Parent process waits for all child processes to finish
*	Also saves the exit status of the last command (for $?)
*/
static void	parent(t_minihell *mini)
{
	int		status;
	int		i;
	t_cmds	*tmp;

	i = 0;
	status = 0;
	close_pipes(mini);
	tmp = mini->cmds;
	while (i < mini->nb_cmds)
	{
		if (mini->pids[i] != -2)
			waitpid(mini->pids[i], &status, 0);
		if (WIFEXITED(status) && (!check_builtin(mini->cmds->command) || \
		((check_builtin(mini->cmds->command) && mini->nb_cmds != 1))))
			mini->error_code = WEXITSTATUS(status);
		if (WTERMSIG(status))
			mini->error_code = 128 + WTERMSIG(status);
		i++;
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = tmp;
}

static bool	execute_continue(t_minihell *mini, int i)
{
	open_files(mini, i, false);
	if (pipe(mini->pipe_fds[i]) == -1)
	{
		perror(strerror(errno));
		mini->error_code = errno;
		return (false);
	}
	if (check_builtin(mini->cmds->command) && mini->nb_cmds == 1)
		solo_builtin(mini, i);
	else
		mini->pids[i] = fork();
	if (mini->pids[i] == -1)
	{
		perror(strerror(errno));
		mini->error_code = errno;
		return (false);
	}
	else if (mini->pids[i] == 0)
		child(mini->cmds, mini, i);
	else
		close(mini->pipe_fds[i][1]);
	return (true);
}

/*	execute()
*	Execute the command line
*	minihell->error_code is set to the exit status of the last command
*	Returns TRUE if execution was successful, FALSE otherwise
*/
void	execute(t_minihell *mini)
{
	t_cmds	*head;
	int		i;

	prepare_execution(mini);
	head = mini->cmds;
	i = 0;
	while (mini->cmds)
	{
		if (g_global.signal_sigint == 1)
			break ;
		if (!execute_continue(mini, i))
			break ;
		i++;
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = head;
	parent(mini);
}
