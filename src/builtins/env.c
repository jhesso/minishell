/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:51:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/05 12:47:55 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_minihell *minihell)
{
	int	i;
	int	argv_size;

	i = 0;
	argv_size = count_strings(minihell->lst_tokens->argv);
	if (argv_size == 1)
	{
		while (minihell->env[i])
		{
			printf("%s\n", minihell->env[i]);
			i++;
		}
		global.error_code = 0;
	}
	else
	{
		ft_printf(2, "env: %s: No such file or directory\n", minihell->lst_tokens->argv[1]);
		global.error_code = 127;
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
