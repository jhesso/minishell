/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:19:14 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/13 20:00:47 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo\0", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd\0", 3))
		return (2);
	else if (!ft_strncmp(cmd, "pwd\0", 4))
		return (3);
	else if (!ft_strncmp(cmd, "export\0", 7))
		return (4);
	else if (!ft_strncmp(cmd, "unset\0", 6))
		return (5);
	else if (!ft_strncmp(cmd, "env\0", 4))
		return (6);
	else if (!ft_strncmp(cmd, "exit\0", 5))
		return (7);
	else
		return (0);
	return (i);
}

int	invalid_variable(t_minihell *minihell, char *arg, int type)
{
	if (type == 1)
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", arg);
	if (type == 2)
		ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", arg);
	minihell->error_code = 1;
	return (1);
}

int	already_exists(char **env, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[len] != '=')
		len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, len))
			return (0);
		i++;
	}
	return (1);
}

void	modify_variable(t_minihell *minihell, char *arg)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (arg[len] != '=')
		len++;
	while (minihell->env[i])
	{
		if (!ft_strncmp(minihell->env[i], arg, len))
		{
			free(minihell->env[i]);
			minihell->env[i] = ft_strdup(arg);
			if (!minihell->env[i])
				malloc_error();
			break ;
		}
		i++;
	}
}

char	**export_variable(char **env, char *arg)
{
	int		amount;
	int		i;
	char	**new_env;

	amount = count_strings(env);
	new_env = malloc(sizeof(char *) * (amount + 2));
	if (!new_env)
		malloc_error();
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			malloc_error();
		free(env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	free(env);
	return (new_env);
}
