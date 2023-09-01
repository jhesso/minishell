/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:25:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/01 17:54:03 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	get_heredoc()
*	Open/create a temporary heredoc file and save user input to it
*	Return value: int (0 if success, -1 if failed)
*	Parameters:
*		(char *) delim: delimiter for heredoc
*/
static int	get_heredoc(char *delim, char *name)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	tmp_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
		return (-1);
	stdin_fd = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0 && \
		line[ft_strlen(delim)] == '\0')
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(stdin_fd);
	close(tmp_fd);
	return (0);
}

int	heredoc(char *delim, char *name)
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = fork();
	ret = 0;
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		printf("hello from the otter slide\n");
		ret = get_heredoc(delim, name);
		if (ret == -1)
		{
			perror(strerror(errno));
			exit (1);
		}
		printf("bye bye :)\n");
		exit (0);
	}
	else
	{
		printf("parent is waiting ...\n");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			error_code = WEXITSTATUS(status);
		printf("the wait is over. exit status was: %d\n", error_code);
	}
	return (error_code); //! this needs to be tested
}

void	get_heredoc_name(t_minihell *mini, int cmd)
{
	char	*nb;

	mini->heredoc_nb = cmd;
	nb = ft_itoa(cmd);
	if (!nb)
		malloc_error();
	mini->heredocs[cmd] = ft_strjoin(".heredoc.tmp", nb);
	if (!mini->heredocs[cmd])
		malloc_error();
	free(nb);
}
