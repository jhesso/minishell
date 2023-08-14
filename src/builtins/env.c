/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:51:46 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/14 14:11:25 by dgerguri         ###   ########.fr       */
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
		malloc_error();
	i = 0;
	while (envp[i])
	{
		minihell->env[i] = ft_strdup(envp[i]);
		if (!minihell->env[i])
			malloc_error();
		i++;
	}
}
