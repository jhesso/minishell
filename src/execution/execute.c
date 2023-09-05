/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/05 14:15:48 by dgerguri         ###   ########.fr       */
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
		exit(error_code) ;
	redirect_io(cmd, mini->pipe_fds, not_first_cmd);
	close(mini->pipe_fds[not_first_cmd][0]);
	if (check_builtin(cmd->command))
	{
		execute_builtin(mini, check_builtin(cmd->command));
		exit(error_code);
	}
	if (execve(cmd->command, cmd->argv, mini->env) == -1)
	{
		perror(strerror(errno));
		error_code = errno;
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

	i = 0;
	usleep(1000);
	close_pipes(mini);
	while(i < mini->nb_cmds)
	{
		if (mini->pids[i] != -2)
			waitpid(mini->pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		error_code = WEXITSTATUS(status);
}

static void	print_fds(t_tokens *lst_tokens)
{
	if (lst_tokens) // changed it an if, because we are going to print it for each node!
	{
		printf("fd_in: %d, fd_out: %d\n", lst_tokens->fd_in, lst_tokens->fd_out);
		// lst_tokens = lst_tokens->next;
	}
}

/*	execute()
*	Execute the command line
*	error_code is set to the exit status of the last command
*	Returns TRUE if execution was successful, FALSE otherwise
*/
bool	execute(t_minihell *minihell)
{
	t_tokens	*head;
	int			i;
	int			status;
	int			stdout_cpy;

	prepare_execution(minihell);
	head = minihell->lst_tokens;
	i = 0;
	while (minihell->lst_tokens)
	{
		open_files(minihell, minihell->lst_tokens);
		print_fds(minihell->lst_tokens);
		status = pipe(minihell->pipe_fds[i]);
		if (status == -1)
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		if (minihell->lst_tokens->fd_in == -1)
		{
			free(minihell->lst_tokens->command);
			minihell->lst_tokens->command = NULL;
		}
		if (check_builtin(minihell->lst_tokens->command) && minihell->nb_cmds == 1)
		{
			if (minihell->lst_tokens->fd_out > 0)
				stdout_cpy = dup(STDOUT_FILENO);
			if (minihell->lst_tokens->fd_out > 0)
				stdout_cpy = dup(STDOUT_FILENO);
			redirect_io(minihell->lst_tokens, minihell->pipe_fds, i);
			close_pipes(minihell);
			execute_builtin(minihell, check_builtin(minihell->lst_tokens->command));
			dup2(stdout_cpy, STDOUT_FILENO);
		}
		else
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
			close(minihell->pipe_fds[i][1]);
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	parent(minihell);
	unlink(".heredoc.tmp");
	minihell->lst_tokens = head;
	return (true);
}
