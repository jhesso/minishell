/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:25:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/05 11:59:53 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int sign)
{
	(void)sign;
	printf("SIGINT\n");
	exit (0);
}

/*	get_heredoc()
*	Open/create a temporary heredoc file and save user input to it
*	Return value: int (0 if success, -1 if failed)
*	Parameters:
*		(char *) delim: delimiter for heredoc
*		(char *) name: name of the heredoc file
*/
static int	get_heredoc(char *delim, char *name)
{
	char	*line;
	int		tmp_fd;
	struct sigaction	sa;

    sa.sa_handler = &heredoc_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("sigaction");
        return (-1);
    }
	tmp_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || (ft_strncmp(line, delim, ft_strlen(delim)) == 0 && \
		line[ft_strlen(delim)] == '\0'))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	return (0);
}

static void	heredoc_child(char *delim, char *name)
{
	int	ret;

	ret = 0;
	ret = get_heredoc(delim, name);
	if (ret == -1)
	{
		perror(strerror(errno));
		exit (1);
	}
	exit (0);
}

int	heredoc(char *delim, char *name)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc_child(delim, name);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			error_code = WEXITSTATUS(status);
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
