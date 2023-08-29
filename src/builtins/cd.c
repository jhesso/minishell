/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:11:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/29 22:24:14 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static void	modify_variable(t_minihell *minihell, char *arg)
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

static char	**export_variable(char **env, char *arg)
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

void	cd_builtin(t_minihell *minihell)
{
	int		argv_size;
	char	*old_pwd;
	char	*home;
	char	*pwd;
	int		flag;

	flag = 0;
	argv_size = count_strings(minihell->lst_tokens->argv);
	old_pwd = ft_strjoin("OLDPWD=", get_value(ft_strdup("$PWD="), 5, minihell->env));
	if (!old_pwd)
		malloc_error();
	home = get_value(ft_strdup("$HOME="), 6, minihell->env);
	pwd = ft_strjoin("PWD=", home);
	if (!pwd)
		malloc_error();
	if (argv_size == 1)
		chdir(home);
	else if (chdir(minihell->lst_tokens->argv[1]))
	{
		if (minihell->lst_tokens->argv[1][0] == '.')
			printf("minishell: cd: %s: Not a directory\n", minihell->lst_tokens->argv[1]);
		else
			printf("minishell: cd: %s: No such file or directory\n", minihell->lst_tokens->argv[1]);
		flag = 1;
	}
	if (!flag)
	{
		if (!already_exists(minihell->env, old_pwd))
			modify_variable(minihell, old_pwd);
		else
			minihell->env = export_variable(minihell->env, old_pwd);
		modify_variable(minihell, pwd);
	}
}
