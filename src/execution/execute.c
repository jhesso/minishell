/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/25 21:07:51 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(t_minihell *mini)
{
	int	i;

	i = 0;
	while (i < mini->nb_cmds)
	{
		close(mini->pipe_fds[i][0]);
		close(mini->pipe_fds[i][1]);
		i++;
	}
}

/*	redirect_io()
*	Redirects input and output to either specified files or to a pipe
*	Close unused file descriptors
*/
static void	redirect_io(t_tokens *cmd, int **pipe_fds, int not_first_cmd, int pipe_read)
{
	if (cmd->fd_in > 0)
	{
		printf("duping STDIN_FILENO to fd_in\n");
		dup2(cmd->fd_in, STDIN_FILENO);
		close(pipe_read);
	}
	else if (not_first_cmd)
	{
		printf("duping STDIN_FILENO to pipe_read\n");
		dup2(pipe_read, STDIN_FILENO);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
	}
	if (cmd->fd_out > 0)
	{
		printf("duping STDOUT_FILENO to fd_out\n");
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(pipe_fds[not_first_cmd][1]);
	}
	else if (cmd->next)
	{
		printf("duping STDOUT_FILENO to pipe_fds[1]\n");
		dup2(pipe_fds[not_first_cmd][1], STDOUT_FILENO);
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
	}
	if (!cmd->next)
		close(pipe_fds[not_first_cmd][1]);
	if (!not_first_cmd && !check_builtin(cmd->command))
		close(pipe_read);
}

/*	child()
*	Child process executes the command and/or builtin function
*	redirects input and output to either specified files or to a pipe
*/
static void	child(t_tokens *cmd, t_minihell *mini, int not_first_cmd, int pipe_read)
{
	if (!cmd->command || check_builtin(cmd->command))
		exit(0) ;
	redirect_io(cmd, mini->pipe_fds, not_first_cmd, pipe_read);
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
	while(i < mini->nb_cmds) //? should this be nb_cmds - 1 ?
		waitpid(mini->pids[i++], &status, 0);
	if (WIFEXITED(status))
		error_code = WEXITSTATUS(status);
	close_pipes(mini);
}

// static void	print_fds(t_tokens *lst_tokens)
// {
// 	while (lst_tokens)
// 	{
// 		printf("fd_in: %d, fd_out: %d\n", lst_tokens->fd_in, lst_tokens->fd_out);
// 		lst_tokens = lst_tokens->next;
// 	}
// }

/*	execute()
*	Execute the command line
*	error_code is set to the exit status of the last command
*	Returns TRUE if execution was successful, FALSE otherwise
*/
bool	execute(t_minihell *minihell)
{ //! Realized a potential problem with heredoc: if more than one command has heredoc as input, only the last commands heredoc will be kept
	t_tokens	*head;
	int			i;
	int			pipe_read = 0;
	int			status;

	prepare_execution(minihell);
	// print_fds(minihell->lst_tokens);
	head = minihell->lst_tokens;
	i = 0;
	while (minihell->lst_tokens)
	{
		status = pipe(minihell->pipe_fds[i]);
		if (status == -1)
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		if (check_builtin(minihell->lst_tokens->command))
		{
			redirect_io(minihell->lst_tokens, minihell->pipe_fds, i, pipe_read);
			execute_builtin(minihell, check_builtin(minihell->lst_tokens->command));
		}
		minihell->pids[i] = fork();
		if (minihell->pids[i] == -1)
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		else if (minihell->pids[i] == 0)
			child(minihell->lst_tokens, minihell, i, pipe_read);
		else
			close(minihell->pipe_fds[i][1]);
		pipe_read = minihell->pipe_fds[i][0];
		if (i)
			close(minihell->pipe_fds[i][0]);
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	parent(minihell);
	close(pipe_read);
	unlink(".heredoc.tmp");
	minihell->lst_tokens = head;
	return (true);
}
