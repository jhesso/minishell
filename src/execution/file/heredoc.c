/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:25:07 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/09 22:50:59 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	get_heredoc()
*	Open/create a temporary heredoc file and save user input to it
*/
static int	write_line(char *line, char *delim, int fd)
{
	char	*doc;

	if (!line && !errno)
	{
		g_global.error_code = 256;
		rl_redisplay();
		return (1);
	}
	if ((ft_strncmp(line, delim, ft_strlen(delim)) == 0 && \
		line[ft_strlen(delim)] == '\0'))
	{
		free(line);
		return (1);
	}
	doc = ft_strjoin(line, "\n");
	if (!doc)
		malloc_error();
	free(line);
	if (write(fd, doc, ft_strlen(doc)) == -1)
		perror(strerror(errno));
	free(doc);
	return (0);
}

static int	get_heredoc(char *delim, char *name)
{
	int		fd;
	char	*line;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf(2, "minishell: heredoc: Could not open heredoc\n");
		return (-1);
	}
	while (g_global.heredoc_signal)
	{
		signal(SIGINT, heredoc_sigint);
		line = readline("> ");
		if (write_line(line, delim, fd))
			break ;
	}
	close(fd);
	if (!g_global.heredoc_signal)
		unlink(name);
	return (0);
}

int	heredoc(char *delim, char *name, t_minihell *mini)
{
	int					ret;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	g_global.heredoc_signal = true;
	ret = get_heredoc(delim, name);
	if (ret == -1)
	{
		perror(strerror(errno));
		g_global.error_code = 1;
	}
	else if (access(name, F_OK) == -1)
	{
		g_global.error_code = 1;
		free(mini->cmds->command);
		mini->cmds->command = NULL;
	}
	else
		g_global.error_code = 0;
	signal(SIGQUIT, handle_cmd);
	signal(SIGINT, handle_cmd);
	printf("error_code: %d\n", g_global.error_code);
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
