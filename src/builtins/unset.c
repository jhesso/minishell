/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:11:25 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/07 14:25:32 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_validity(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || arg[i] == '=' || arg[i] == '+' || ft_isdigit(arg[i]))
		return (invalid_variable(arg, 2));
	while (arg[i])
	{
		if (ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_')
			i++;
		else if (arg[i] == '=')
			return (invalid_variable(arg, 2));
		else
			return (invalid_variable(arg, 2));
	}
	return (0);
}

static int	identifier_exists(char **env, char *arg)
{
	int	i;
	int	env_len;
	int	arg_len;

	i = 0;
	arg_len = ft_strlen(arg);
	while (env[i])
	{
		env_len = 0;
		while (env[i][env_len] != '=')
			env_len++;
		if (env_len == arg_len)
		{
			if (!ft_strncmp(env[i], arg, arg_len))
				return (i + 1);
		}
		i++;
	}
	return (0);
}

static char	**remove_variable(char **env, int remove_env)
{
	int		amount;
	int		i;
	int		j;
	char	**new_env;

	amount = count_strings(env);
	new_env = malloc(sizeof(char *) * (amount));
	if (!new_env)
		malloc_error();
	i = 0;
	j = 0;
	while (env[i])
	{
		if (env[i] && i != remove_env)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				malloc_error();
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_str_arr(env);
	return (new_env);
}

void	unset_builtin(t_minihell *mini)
{
	int	i;
	int	remove_env;

	i = 1;
	g_global.error_code = 0;
	while (mini->cmds->argv[i])
	{
		if (!check_validity(mini->cmds->argv[i]))
		{
			remove_env = identifier_exists(mini->env, mini->cmds->argv[i]);
			if (remove_env)
				mini->env = remove_variable(mini->env, remove_env - 1);
		}
		i++;
	}
}
