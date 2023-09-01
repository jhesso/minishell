/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/01 17:14:14 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	redirect_io()
*	Redirects input and output to either specified files or to a pipe
*	Close unused file descriptors
*/
static void	redirect_io(t_tokens *cmd, int **pipe_fds, int nb_cmd, int log)
{
	dprintf(log, "nb_cmd: %d cmd: %s\n", nb_cmd, cmd->command);
	if (cmd->fd_in > 0 && !check_builtin(cmd->command))
	{
		dprintf(log, "redirecting STDIN_FILENO into cmd->fd_in\n");
		dup2(cmd->fd_in, STDIN_FILENO);
	}
	else if (nb_cmd)
	{
		dprintf(log, "redirecting STDIN_FILENO into pipe_fds[%d][0]\n", nb_cmd - 1);
		dup2(pipe_fds[nb_cmd - 1][0], STDIN_FILENO);
		// close(pipe_fds[nb_cmd - 1][0]);
	}
	if (cmd->fd_out > 0)
	{
		dprintf(log, "redirecting STDOUT_FILENO into cmd->fd_out\n");
		dup2(cmd->fd_out, STDOUT_FILENO);
		// close(pipe_fds[nb_cmd][1]);
	}
	else if (cmd->next)
	{
		dprintf(log, "redirecting STDOUT_FILENO into pipe_fds[%d][1]\n", nb_cmd);
		dup2(pipe_fds[nb_cmd][1], STDOUT_FILENO);
		close(pipe_fds[nb_cmd][1]);
	}
}

/*	child()
*	Child process executes the command and/or builtin function
*	redirects input and output to either specified files or to a pipe
*/
static void	child(t_tokens *cmd, t_minihell *mini, int not_first_cmd, int log)
{
	if (!cmd->command)
		exit(error_code) ;
	redirect_io(cmd, mini->pipe_fds, not_first_cmd, log);
	if (check_builtin(cmd->command))
	{
		execute_builtin(mini, check_builtin(cmd->command));
		exit(error_code);
	}
	close(log);
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
static void	parent(t_minihell *mini, int log)
{
	int		status;
	int		i;

	i = 0;
	usleep(1000);
	dprintf(log, "waiting for children to finish...\n");
	while(i < mini->nb_cmds)
	{
		dprintf(log, "PID: %d\n", mini->pids[i]);
		if (mini->pids[i] != -2)
			waitpid(mini->pids[i], &status, 0);
		dprintf(log, "i: %d\n", i);
		if (WIFEXITED(status))
			error_code = WEXITSTATUS(status);
		i++;
	}
	dprintf(log, "done waiting :)\n");
	close_pipes(mini);
}

// static void	print_fds(t_tokens *lst_tokens)
// {
// 	if (lst_tokens) // changed it an if, because we are going to print it for each node!
// 	{
// 		printf("fd_in: %d, fd_out: %d\n", lst_tokens->fd_in, lst_tokens->fd_out);
// 		// lst_tokens = lst_tokens->next;
// 	}
// }

static int	open_log(t_minihell *minihell)
{
	int		fd;
	char	*path;
	char	*log_path;

	path = get_value(ft_strdup("$HOME="), 6, minihell->env);
	if (!path)
		perror(strerror(errno));
	log_path = ft_strjoin(path, "/log.txt");
	if (!log_path)
		perror("strjoin fail");
	free(path);
	fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(strerror(errno));
	free(log_path);
	return (fd);
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
	int			log;
	int			stdout_cpy;

	prepare_execution(minihell);
	head = minihell->lst_tokens;
	i = 0;
	log = open_log(minihell);
	if (log < 0)
		return (false);
	while (minihell->lst_tokens)
	{
		open_files(minihell, minihell->lst_tokens, i);
		// print_fds(minihell->lst_tokens);
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
			{
				dprintf(log, "duplicating STDOUT_FILENO\n");
				stdout_cpy = dup(STDOUT_FILENO);
			}
			redirect_io(minihell->lst_tokens, minihell->pipe_fds, i, log);
			close_pipes(minihell);
			dprintf(log, "fd_out: %d\n", minihell->lst_tokens->fd_out);
			execute_builtin(minihell, check_builtin(minihell->lst_tokens->command));
			dprintf(log, "builtin executed\n");
			dup2(stdout_cpy, STDOUT_FILENO);
			dprintf(log, "----------------------------\n");
			close(log);
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
			child(minihell->lst_tokens, minihell, i, log);
		else
			close(minihell->pipe_fds[i][1]);
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	parent(minihell, log);
	dprintf(log, "exit_code: %d\n", error_code);
	dprintf(log, "----------------------------\n");
	close(log);
	minihell->lst_tokens = head;
	return (true);
}
