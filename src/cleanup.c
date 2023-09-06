/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:22:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 18:58:46 by jhesso           ###   ########.fr       */
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
*	frees the lst_tokens linked list and all of its contents
*/
static void	free_list(t_tokens *lst_tokens)
{
	t_tokens	*tmp;

	while (lst_tokens)
	{
		tmp = lst_tokens;
		lst_tokens = lst_tokens->next;
		if (tmp->command)
			free(tmp->command);
		if (tmp->fd_in > 0)
			close(tmp->fd_in);
		if (tmp->fd_out > 0)
			close(tmp->fd_out);
		free_str_arr(tmp->opt);
		free(tmp->argv[0]);
		free(tmp->argv);
		free(tmp);
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

	free_list(minihell->lst_tokens);
	free_str_arr(minihell->tokens);
	free(minihell->pids);
	i = 0;
	while (i < minihell->nb_cmds)
	{
		free(minihell->pipe_fds[i]);
		i++;
	}
	free(minihell->pipe_fds);
	close_heredocs(minihell);
}
