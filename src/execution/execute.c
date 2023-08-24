/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/24 03:43:01 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	redirect_io()
*	Redirects input and output to either specified files or to a pipe
*	Close unused file descriptors
*/
static void	redirect_io(t_tokens *cmd, int *pipe_fds, int not_first_cmd, int pipe_read)
{
	if (cmd->fd_in > 0) //* if input is redirected to a file
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(pipe_read);
	}
	else if (not_first_cmd) //* if not first command, redirect input to pipe
	{
		dup2(pipe_read, STDIN_FILENO);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
	}
	if (cmd->fd_out > 0) //* if output is redirected to a file
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else if (cmd->next) //* if not last command, redirect output to pipe
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		if (cmd->fd_out != 0)
			close(cmd->fd_out);
	}
	if (!cmd->next) //* if last command, close write end of pipe
		close(pipe_fds[1]);
	if (!not_first_cmd) //* if first command, close read end of pipe
		close(pipe_read);
}

/*	child()
*	Child process executes the command and/or builtin function
*	redirects input and output to either specified files or to a pipe
*/
static void	child(t_tokens *cmd, t_minihell *mini, int not_first_cmd, int pipe_read)
{
	int	builtin;

	if (!cmd->command) //* if command is NULL, exit (this is for when a command was false)
		return ;
	redirect_io(cmd, mini->pipe_fds, not_first_cmd, pipe_read); //* redirect input and output to their proper places
	builtin = check_builtin(cmd->command); //* check if command is a builtin
	if (builtin > 0)
		execute_builtin(mini, builtin); //* execute builtin
	else if (execve(cmd->command, cmd->argv, mini->env) == -1) //* execute command
	{
		perror(strerror(errno)); //* if execve fails, print error and save error code
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
		error_code = WEXITSTATUS(status); //* save exit status of last command
}

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

	// print_string_arr(minihell->tokens);
	// lst_print(minihell->lst_tokens);
	prepare_execution(minihell);
	head = minihell->lst_tokens;
	i = 0;
	while (minihell->lst_tokens)
	{
		if (pipe(minihell->pipe_fds) == -1) //* create pipe
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		minihell->pids[i] = fork(); //* create child process
		if (minihell->pids[i] == -1) //* if fork fails
		{
			perror(strerror(errno));
			error_code = errno;
			break ;
		}
		else if (minihell->pids[i] == 0) //* child process
			child(minihell->lst_tokens, minihell, i, pipe_read);
		else
			close(minihell->pipe_fds[1]); //* parent process can close the write end of the pipe
		if (minihell->pids[i] == 0) //* if child process reaches here, exit (mainly for false commands) but also if execve fails
			exit(error_code);
		pipe_read = minihell->pipe_fds[0]; //* save the read end of the pipe for the next command
		if (i)
			close(minihell->pipe_fds[0]); //* if not first command, close the read end of the pipe
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	parent(minihell); //* parent process waits for all child processes to finish
	//TODO: unlink heredoc
	minihell->lst_tokens = head;
	return (true);
}
