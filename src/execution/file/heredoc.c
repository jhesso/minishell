/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:25:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/09 19:17:39 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	g_global.heredoc_tmp = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	g_global.heredoc_tmp_name = name;
	if (g_global.heredoc_tmp == -1)
		return (-1);
	while (true)
	{
		line = readline("> ");
		if (line == NULL || (ft_strncmp(line, delim, ft_strlen(delim)) == 0 && \
		line[ft_strlen(delim)] == '\0'))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, g_global.heredoc_tmp);
		free(line);
	}
	close(g_global.heredoc_tmp);
	// if (g_global.heredoc_interrupt)
	// 	unlink(name);
	return (0);
}

static void	heredoc_child(char *delim, char *name)
{
	int					ret;
	struct sigaction	sa;

	signal(SIGINT, SIG_DFL);
	sa.sa_handler = &heredoc_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit (1);
	}
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
	// int		i;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		heredoc_child(delim, name);
	else
		waitpid(pid, &status, 0);
	// i = 0;
	// while (i < 1000)
	// 	i++;
	// printf("done waiting\n");
	// sleep(10);
	// if (WIFSIGNALED(status))
	// {
	// 	printf("signaled\n");
	// 	unlink(name);
	// }
	if (access(name, F_OK) == -1)
		g_global.error_code = 1;
	else
		g_global.error_code = 0;
	return (g_global.error_code);
}

void	get_heredoc_name(t_minihell *mini, int cmd)
{
	char	*nb;
	char	*path;
	char	*name;

	mini->heredoc_nb = cmd;
	path = get_value(ft_strdup("$_="), 3, mini->env);
	if (!*path)
	{
		ft_printf(STDERR_FILENO, "minishell: error: no path for heredoc\n");
		exit(1);
	}
	name = ft_strjoin(path, ".heredoc.tmp");
	nb = get_num(name, cmd);
	mini->heredocs[cmd] = ft_strjoin(name, nb);
	if (!mini->heredocs[cmd])
		malloc_error();
	free(path);
	free(name);
	free(nb);
}
