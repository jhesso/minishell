/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:17:54 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/13 23:06:38 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_validity(t_minihell *minihell, char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || arg[i] == '=' || arg[i] == '+' || ft_isdigit(arg[i]))
		return (invalid_variable(minihell, arg, 1));
	while (arg[i])
	{
		if (ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_')
			i++;
		else if (arg[i] == '=')
			break ;
		else
			return (invalid_variable(minihell, arg, 1));
	}
	return (0);
}

void	export_builtin(t_minihell *mini, int i, int argv_size)
{
	mini->error_code = 0;
	argv_size = count_strings(mini->cmds->argv);
	if (argv_size == 1)
		while (mini->env[i])
			printf("declare -x %s\n", mini->env[i++]);
	else
	{
		i = 1;
		while (mini->cmds->argv[i])
		{
			if (!check_validity(mini, mini->cmds->argv[i]))
			{
				if (ft_strrchr(mini->cmds->argv[i], '='))
				{
					if (already_exists(mini, mini->cmds->argv[i], 0, 0))
						mini->env = export_variable(mini->env, \
						mini->cmds->argv[i]);
				}
			}
			i++;
		}
	}
}
