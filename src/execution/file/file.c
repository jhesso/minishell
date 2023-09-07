/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:21:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/07 16:31:24 by dgerguri         ###   ########.fr       */
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
	return (fd);
}

static int	file_error(t_minihell *mini, int i, bool *error_flag)
{
	char	*error;

	if (!mini->tokens[i])
		mini->tokens[i] = ft_calloc(1, 1);
	if (!mini->tokens[i])
		malloc_error();
	error = mini->tokens[i];
	while (mini->tokens[i + 1] && mini->tokens[i][0] != '|')
	{
		if (!ft_strncmp(mini->tokens[i++], "<<\0", 3))
		{
			if (mini->cmds->fd_in > 0)
				close(mini->cmds->fd_in);
			mini->tokens[i] = remove_quotes(mini->tokens[i], 0, 0, 0);
			mini->cmds->fd_in = open_file(mini->tokens[i], 1, mini);
		}
	}
	ft_printf(2, "minishell: %s: No such file or directory\n", error);
	g_global.error_code = 1;
	*(error_flag) = true;
	free(mini->cmds->command);
	mini->cmds->command = NULL;
	return (i);
}

static int	open_input(t_minihell *minihell, int i, bool *error_flag)
{
	if (!ft_strncmp(minihell->tokens[i - 1], "<\0", 2))
	{
		if (minihell->cmds->fd_in > 0)
			close(minihell->cmds->fd_in);
		minihell->tokens[i] = remove_quotes(minihell->tokens[i], 0, 0, 0);
		minihell->cmds->fd_in = open_file(minihell->tokens[i], 0, NULL);
		if (minihell->cmds->fd_in == -1)
			i = file_error(minihell, i, error_flag);
	}
	else if (!ft_strncmp(minihell->tokens[i - 1], "<<\0", 3))
	{
		if (minihell->cmds->fd_in > 0)
			close(minihell->cmds->fd_in);
		minihell->tokens[i] = remove_quotes(minihell->tokens[i], 0, 0, 0);
		minihell->cmds->fd_in = open_file(minihell->tokens[i], 1, minihell);
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
static int	open_output(t_minihell *mini, int i, bool *flag, bool *error_flag)
{
	if (!ft_strncmp(mini->tokens[i - 1], ">\0", 2))
	{
		if (mini->cmds->fd_out > 0)
			close(mini->cmds->fd_out);
		*(flag) = true;
		mini->tokens[i] = remove_quotes(mini->tokens[i], 0, 0, 0);
		mini->cmds->fd_out = open_file(mini->tokens[i], 2, NULL);
	}
	else if (!ft_strncmp(mini->tokens[i - 1], ">>\0", 3) && *(flag) == false)
	{
		if (mini->cmds->fd_out > 0)
			close(mini->cmds->fd_out);
		mini->tokens[i] = remove_quotes(mini->tokens[i], 0, 0, 0);
		mini->cmds->fd_out = open_file(mini->tokens[i], 3, NULL);
	}
	else if (!ft_strncmp(mini->tokens[i - 1], ">>\0", 3) && *(flag) == true)
	{
		if (mini->cmds->fd_out > 0)
			close(mini->cmds->fd_out);
		mini->tokens[i] = remove_quotes(mini->tokens[i], 0, 0, 0);
		mini->cmds->fd_out = open_file(mini->tokens[i], 2, NULL);
	}
	if (mini->cmds->fd_out == -1)
		i = file_error(mini, i, error_flag);
	return (i);
}

void	open_files(t_minihell *mini, int cmd, bool flag, bool error_flag)
{
	static int	i = 0;

	mini->cmds->fd_in = 0;
	mini->cmds->fd_out = 0;
	get_heredoc_name(mini, cmd);
	while (mini->tokens[i] && mini->tokens[i][0] != '|' && error_flag == false)
	{
		if (mini->tokens[i][0] == '<')
			i = open_input(mini, i + 1, &error_flag);
		else if (mini->tokens[i][0] == '>')
			i = open_output(mini, i + 1, &flag, &error_flag);
		i++;
	}
	if (mini->tokens[i] && mini->tokens[i][0] == '|')
		i++;
	if (!mini->tokens[i])
		i = 0;
	if (error_flag == false)
		append_command_path(mini, mini->cmds);
	else
	{
		free(mini->cmds->command);
		mini->cmds->command = NULL;
	}
}
