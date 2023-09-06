/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:26:39 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 19:55:00 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_argv(t_minihell *minihell, t_tokens *tmp, int i, int options)
{
	tmp = minihell->cmds;
	while (minihell->cmds != NULL)
	{
		options = count_strings(minihell->cmds->opt);
		minihell->cmds->argv = malloc(sizeof(char *) * (options + 2));
		if (!minihell->cmds->argv)
			malloc_error();
		if (!minihell->cmds->command)
			minihell->cmds->argv[0] = NULL;
		else
		{
			minihell->cmds->argv[0] = ft_strdup(minihell->cmds->command);
			if (!minihell->cmds->argv[0])
				malloc_error();
		}
		i = 0;
		while (minihell->cmds->opt[i])
		{
			minihell->cmds->argv[i + 1] = minihell->cmds->opt[i];
			i++;
		}
		minihell->cmds->argv[i + 1] = NULL;
		minihell->cmds = minihell->cmds->next;
	}
	minihell->cmds = tmp;
}
