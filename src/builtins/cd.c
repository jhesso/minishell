/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:11:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/31 17:45:10 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_env(t_minihell *minihell, char *old_pwd, char *home, int flag)
{
	char *pwd;

	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!pwd)
		malloc_error();
	if (!flag)
	{
		if (!already_exists(minihell->env, old_pwd))
			modify_variable(minihell, old_pwd);
		else
			minihell->env = export_variable(minihell->env, old_pwd);
		modify_variable(minihell, pwd);
		error_code = 0;
	}
	else
		error_code = 1;
	free(old_pwd);
	free(home);
	free(pwd);
}

void	cd_builtin(t_minihell *minihell)
{
	char	*old_pwd;
	char	*home;
	int		flag;

	flag = 0;
	old_pwd = ft_strjoin("OLDPWD=", get_value(ft_strdup("$PWD="), 5, minihell->env));
	home = get_value(ft_strdup("$HOME="), 6, minihell->env);
	if (!old_pwd || !home)
		malloc_error();
	if (count_strings(minihell->lst_tokens->argv) == 1)
	{
		if (chdir(home))
		{
			ft_printf(2, "minishell: cd: HOME not set\n");
			flag = 1;
		}
	}
	else if (chdir(minihell->lst_tokens->argv[1]))
	{
		if (minihell->lst_tokens->argv[1][0] == '.')
			ft_printf(2, "minishell: cd: %s: Not a directory\n", minihell->lst_tokens->argv[1]);
		else
			ft_printf(2, "minishell: cd: %s: No such file or directory\n", minihell->lst_tokens->argv[1]);
		flag = 1;
	}
	modify_env(minihell, old_pwd, home, flag);
}
