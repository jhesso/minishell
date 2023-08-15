/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:51:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/15 17:51:22 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_minihell *minihell)
{
	int	i;

	i = 0;
	while (minihell->env[i])
	{
		printf("%s\n", minihell->env[i]);
		i++;
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
