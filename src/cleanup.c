/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:22:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/07 22:23:49 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_minihell *mini)
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

static void	close_heredocs(t_minihell *mini)
{
	int	i;

	i = 0;
	while (mini->heredocs[i])
	{
		unlink(mini->heredocs[i]);
		free(mini->heredocs[i]);
		i++;
	}
	free(mini->heredocs);
}

/*	free_list()
*	frees the cmds linked list and all of its contents
*/
static void	free_list(t_cmds *cmds)
{
	t_cmds	*tmp;
	int		i = 0;

	while (cmds)
	{
		printf("freeing list node: %d\n", i);
		tmp = cmds;
		cmds = cmds->next;
		printf("tmp->command: %s\n", tmp->command);
		if (tmp->command)
			free(tmp->command);
		if (tmp->fd_in > 0)
			close(tmp->fd_in);
		if (tmp->fd_out > 0)
			close(tmp->fd_out);
		printf("tmp->opt:\n");
		print_string_arr(tmp->opt);
		free_str_arr(tmp->opt);
		free(tmp->argv[0]);
		free(tmp->argv);
		free(tmp);
		i++;
	}
}

/*	cleanup()
*	frees all the allocated memory in preparation
*	for the next command line
*	note, does not free env as we need it until the end
*/
void	cleanup(t_minihell *minihell)
{
	int	i;

	free_list(minihell->cmds);
	printf("freeing char** tokens:\n");
	print_string_arr(minihell->tokens);
	free_str_arr(minihell->tokens);
	printf("--------------------------\n");
	printf("freeing minihell->pids:\n");
	free(minihell->pids);
	i = 0;
	printf("--------------------------\n");
	printf("freeing minihell->pipe_fds\n");
	while (i < minihell->nb_cmds)
	{
		free(minihell->pipe_fds[i]);
		i++;
	}
	free(minihell->pipe_fds);
	close_heredocs(minihell);
}
