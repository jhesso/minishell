/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:21:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/17 19:08:41 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_heredoc(char *delim)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	tmp_fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(delim, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	stdin_fd = dup(STDIN_FILENO);
	// dup2(tmp_fd, STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0 &&
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
}

/*	open_file()
*	Opens the given file in the correct mode
*	Returns the file descriptor or -1 if open failed
*/
static int	open_file(char *filename, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(filename, O_RDONLY, 0644);
	else if (mode == 1)
	{
		get_heredoc(filename);
		fd = open(".heredoc.tmp", O_RDONLY, 0644);
	}
	else if (mode == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_printf("fd: %d\n", fd);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (fd);
}

/*	open_files()
*	1. Allocate memory for fd arrays
*	2. Open files
*	3. create heredoc if needed
*	4. return true if success
*/
void	open_files(t_minihell *minihell)
{
	// t_tokens	*tmp;
	// int			i;
	// int			j;

	// tmp = lst_tokens;
	// while (lst_tokens)
	// {
	// 	allocate_fds(lst_tokens);
	// 	i = 0;
	// 	j = 0;
	// 	while (lst_tokens->in[i])
	// 		lst_tokens->fd_in[j] = open_file(lst_tokens->in[i++], 0);
	// 	i = 0;
	// 	while (lst_tokens->heredoc[i])
	// 		lst_tokens->fd_in[j++] = open_file(lst_tokens->heredoc[i++], 1);
	// 	i = 0;
	// 	j = 0;
	// 	while (lst_tokens->out[i])
	// 		lst_tokens->fd_out[j++] = open_file(lst_tokens->out[i++], 2);
	// 	i = 0;
	// 	while (lst_tokens->out_app[i])
	// 		lst_tokens->fd_out[j++] = open_file(lst_tokens->out_app[i++], 3);
	// 	lst_tokens = lst_tokens->next;
	// }
	// lst_tokens = tmp;
}
