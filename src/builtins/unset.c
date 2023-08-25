/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:11:25 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/25 16:43:48 by dgerguri         ###   ########.fr       */
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
		return (invalid_variable(arg, 2));
	while (arg[i])
	{
		if (ft_isalpha(arg[i]))
			i++;
		else if (ft_isdigit(arg[i]) && !flag)
			return (invalid_variable(arg, 2));
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
			return (invalid_variable(arg, 2));
	}
	return (0);
}

static int		already_exists(char **env, char *arg)
{
	int	i;
	int env_len;
	static int arg_len;

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
char	**remove_variable(char **env, int remove_env)
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
		if (i == remove_env)
			i++;
		new_env[j] = ft_strdup(env[i]);
		if (!new_env[i])
			malloc_error();
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_str_arr(env);
	// int a = 0;
	// while (new_env[a])
	// {
	// 	printf("%s\n", new_env[a]);
	// 	a++;
	// }
	return (new_env);
}

void	unset_builtin(t_minihell *minihell)
{
	int	i;
	int	remove_env;
	int	argv_size;

	i = 1;
	argv_size = count_strings(minihell->lst_tokens->argv);
	while (minihell->lst_tokens->argv[i])
	{
		if (!check_validity(minihell->lst_tokens->argv[i]))
		{
			if (ft_strrchr(minihell->lst_tokens->argv[i], '='))
				invalid_variable(minihell->lst_tokens->argv[i], 2);
			else
			{
				remove_env = already_exists(minihell->env, minihell->lst_tokens->argv[i]);
				if (remove_env)
					minihell->env = remove_variable(minihell->env, remove_env - 1);
			}
		}
		i++;
	}
}
