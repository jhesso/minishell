/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:51:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/06 19:50:32 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_minihell *minihell)
{
	int	i;
	int	argv_size;

	i = 0;
	argv_size = count_strings(minihell->cmds->argv);
	if (argv_size == 1)
	{
		while (minihell->env[i])
		{
			printf("%s\n", minihell->env[i]);
			i++;
		}
		g_global.error_code = 0;
	}
	else
	{
		ft_printf(2, "env: %s: No such file or directory\n", \
			minihell->cmds->argv[1]);
		g_global.error_code = 127;
	}
}

void	init_env(t_minihell *minihell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	minihell->env = malloc(sizeof(char *) * (i + 1));
	if (!minihell->env)
		malloc_error();
	i = 0;
	while (envp[i])
	{
		minihell->env[i] = ft_strdup(envp[i]);
		if (!minihell->env[i])
			malloc_error();
		i++;
	}
	minihell->env[i] = NULL;
}
