/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 03:25:41 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/01 16:34:51 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pids(t_minihell *minihell)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = minihell->lst_tokens;
	while (minihell->lst_tokens)
	{
		i++;
		minihell->lst_tokens = minihell->lst_tokens->next;
	}
	minihell->nb_cmds = i;
	minihell->pids = malloc(sizeof(pid_t) * minihell->nb_cmds);
	if (!minihell->pids)
		malloc_error();
	i = 0;
	while (i < minihell->nb_cmds)
		minihell->pids[i++] = -2;
	minihell->lst_tokens = tmp;
}

void	prepare_execution(t_minihell *minihell)
{
	int i;
	create_argv(minihell);
	init_pids(minihell);
	minihell->pipe_fds = malloc(sizeof(int *) * minihell->nb_cmds);
	if (!minihell->pipe_fds)
		malloc_error();
	i = 0;
	while (i < minihell->nb_cmds)
	{
		minihell->pipe_fds[i] = malloc(sizeof(int) * 2);
		if (!minihell->pipe_fds[i])
			malloc_error();
		i++;
	}
	minihell->heredocs = ft_calloc(minihell->nb_cmds + 1, sizeof(char *));
	if (!minihell->heredocs)
		malloc_error();
}
