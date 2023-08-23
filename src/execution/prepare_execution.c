/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 03:25:41 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 04:16:10 by jhesso           ###   ########.fr       */
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
	minihell->lst_tokens = tmp;
}

void	prepare_execution(t_minihell *minihell)
{
	create_argv(minihell);
	open_files(minihell);
	append_command_path(minihell);
	init_pids(minihell);
}
