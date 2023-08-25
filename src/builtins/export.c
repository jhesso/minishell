/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:17:54 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/25 21:19:33 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_validity(char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (arg[i] == '=' || arg[i] == '+')
		return (invalid_variable(arg, 1));
	while (arg[i])
	{
		if (ft_isalpha(arg[i]))
			i++;
		else if (ft_isdigit(arg[i]) && !flag)
			return (invalid_variable(arg, 1));
		else if (ft_isdigit(arg[i]) && flag)
			i++;
		else if (arg[i] == '_')
		{
			flag = 1;
			i++;
		}
		else if (arg[i] == '=')
			break;
		else
			return (invalid_variable(arg, 1));
	}
	return (0);
}

static int		already_exists(char **env, char *arg)
{
	int	i;
	int len;

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

void	export_builtin(t_minihell *minihell)
{
	int	i;
	int	argv_size;

	i = 0;
	argv_size = count_strings(minihell->lst_tokens->argv);
	if (argv_size == 1)
	{
		while (minihell->env[i])
			printf("declare -x %s\n", minihell->env[i++]);
	}
	else
	{
		i = 1;
		while (minihell->lst_tokens->argv[i])
		{
			if (!check_validity(minihell->lst_tokens->argv[i]))
			{
				if (ft_strrchr(minihell->lst_tokens->argv[i], '='))
				{
					if (!already_exists(minihell->env, minihell->lst_tokens->argv[i]))
						modify_variable(minihell, minihell->lst_tokens->argv[i]);
					else
						minihell->env = export_variable(minihell->env, minihell->lst_tokens->argv[i]);
				}
			}
			i++;
		}
	}
}
