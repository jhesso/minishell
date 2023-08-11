/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:51:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/11 19:19:07 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_minihell *minihell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	minihell->env = malloc(sizeof(char *) * i + 1);
	if (!minihell->env)
	{
		ft_putendl_fd("Error: Malloc error", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		minihell->env[i] = ft_strdup(envp[i]);
		if (!minihell->env[i])
		{
			ft_putendl_fd("Error: Malloc error", STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
		i++;
	}
}
