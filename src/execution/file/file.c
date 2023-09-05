/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:21:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/05 14:26:09 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *filename, int mode, t_minihell *mini)
{
	int			fd;

	if (mode == 0)
		fd = open(filename, O_RDONLY, 0644);
	else if (mode == 1)
	{
		fd = heredoc(filename, mini->heredocs[mini->heredoc_nb]);
		if (fd == 0)
			fd = open(mini->heredocs[mini->heredoc_nb], O_RDONLY, 0644);
	}
	else if (mode == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf(2, "minishell: %s: %s\n", filename, strerror(errno));
		global.error_code = 1;
	}
	return (fd);
}

static int	open_input(t_minihell *minihell, t_tokens *lst_tokens, int i, bool *error_flag)
{
	if (!ft_strncmp(minihell->tokens[i], "<\0", 2))
	{
		if (lst_tokens->fd_in > 0)
			close(lst_tokens->fd_in);
		lst_tokens->fd_in = open_file(minihell->tokens[++i], 0, NULL);
		if (lst_tokens->fd_in == -1)
		{
			while (minihell->tokens[i + 1] && minihell->tokens[i][0] != '|')
				i++;
			*(error_flag) = true;
		}
	}
	else if (!ft_strncmp(minihell->tokens[i], "<<\0", 3))
	{
		if (lst_tokens->fd_in > 0)
			close(lst_tokens->fd_in);
		lst_tokens->fd_in = open_file(minihell->tokens[++i], 1, minihell);
	}
	return (i);
}

/*	open_file()
*	Opens the given file in the correct mode
*	Return value: int (file descriptor. -1 if failed)
*	Parameters:
*		(char *) filename: name of the file to be opened
*		(int) mode: mode for opening the file
*/
static int	open_output(t_minihell *minihell, t_tokens *lst_tokens, int i, bool *flag)
{
	if (!ft_strncmp(minihell->tokens[i], ">\0", 2))
	{
		if (lst_tokens->fd_out > 0)
			close(lst_tokens->fd_out);
		*(flag) = true;
		lst_tokens->fd_out = open_file(minihell->tokens[++i], 2, NULL);
	}
	else if (!ft_strncmp(minihell->tokens[i], ">>\0", 3) && *(flag) == false)
	{
		if (lst_tokens->fd_out > 0)
			close(lst_tokens->fd_out);
		lst_tokens->fd_out = open_file(minihell->tokens[++i], 3, NULL);
	}
	else if (!ft_strncmp(minihell->tokens[i], ">>\0", 3) && *(flag) == true)
	{
		if (lst_tokens->fd_out > 0)
			close(lst_tokens->fd_out);
		lst_tokens->fd_out = open_file(minihell->tokens[++i], 2, NULL);
	}
	return (i);
}

void	open_files(t_minihell *minihell, t_tokens *lst_tokens, int cmd)
{
	static int	i = 0;
	bool		error_flag;
	bool		flag;

	lst_tokens->fd_in = 0;
	lst_tokens->fd_out = 0;
	error_flag = false;
	flag = false;
	get_heredoc_name(minihell, cmd);
	while (minihell->tokens[i] && minihell->tokens[i][0] != '|' && error_flag == false)
	{
		if (minihell->tokens[i][0] == '<' && flag == false)
			i = open_input(minihell, lst_tokens, i, &error_flag);
		else if (minihell->tokens[i][0] == '>')
			i = open_output(minihell, lst_tokens, i, &flag);
		i++;
	}
	if (minihell->tokens[i] && minihell->tokens[i][0] == '|')
		i++;
	if (!minihell->tokens[i])
		i = 0;
	if (error_flag == false)
		append_command_path(minihell, lst_tokens);
	else
	{
		free(minihell->lst_tokens->command);
		minihell->lst_tokens->command = NULL;
	}
}
