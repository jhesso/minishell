/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:11:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/07 14:44:29 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_env(t_minihell *mini, char *old_pwd, char *home, int flag)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!pwd)
		malloc_error();
	if (!flag)
	{
		if (!already_exists(mini->env, old_pwd))
			modify_variable(mini, old_pwd);
		else
			mini->env = export_variable(mini->env, old_pwd);
		if (!already_exists(mini->env, pwd))
			modify_variable(mini, pwd);
		else
			mini->env = export_variable(mini->env, pwd);
		g_global.error_code = 0;
	}
	else
		g_global.error_code = 1;
	free(old_pwd);
	free(home);
	free(pwd);
}

void	cd_builtin(t_minihell *mini, char *old_pwd, char *home, int flag)
{
	old_pwd = ft_strjoin("OLDPWD=", \
	get_value(ft_strdup("$PWD="), 5, mini->env));
	home = get_value(ft_strdup("$HOME="), 6, mini->env);
	if (!old_pwd || !home)
		malloc_error();
	if (count_strings(mini->cmds->argv) == 1)
	{
		if (chdir(home))
		{
			if (!home[0])
				ft_printf(2, "minishell: cd: HOME not set\n");
			else
				ft_printf(2, "minishell: cd: %s: No such file or directory\n", \
				home);
			flag = 1;
		}
	}
	else if (chdir(mini->cmds->argv[1]))
	{
		ft_printf(2, "minishell: cd: %s: %s\n", \
			mini->cmds->argv[1], strerror(errno));
		flag = 1;
	}
	modify_env(mini, old_pwd, home, flag);
}
