/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:19:38 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/06 19:20:03 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_line(t_minihell *minihell, int start, int flag)
{
	if (minihell->cmds->argv[start])
	{
		printf("%s", minihell->cmds->argv[start]);
		start++;
	}
	while (minihell->cmds->argv[start])
	{
		printf(" ");
		printf("%s", minihell->cmds->argv[start]);
		start++;
	}
	if (!flag)
		printf("\n");
}

void	echo_builtin(t_minihell *minihell, int j, int flag, int i)
{
	int	argv_size;

	argv_size = count_strings(minihell->cmds->argv);
	if (argv_size == 1)
		printf("\n");
	else if (argv_size > 1)
	{
		while (!ft_strncmp(minihell->cmds->argv[j], "-n", 2))
		{
			i = 1;
			while (minihell->cmds->argv[j][i] == 'n')
				i++;
			if (j == 1 && !minihell->cmds->argv[j][i])
				flag = 1;
			else if (minihell->cmds->argv[j][i] != '\0')
				break ;
			if (!minihell->cmds->argv[++j])
				break ;
		}
		if (!flag)
			print_line(minihell, 1, flag);
		else
			print_line(minihell, j, flag);
	}
	g_global.error_code = 0;
}
