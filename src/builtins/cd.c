/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:11:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/30 03:53:42 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (argv_size == 1)
	{
		if (!home[0])
			printf("minishell: cd: HOME not set\n");
		else
			chdir(home);
	}
	else if (chdir(minihell->lst_tokens->argv[1]))
	{
		if (minihell->lst_tokens->argv[1][0] == '.')
			printf("minishell: cd: %s: Not a directory\n", minihell->lst_tokens->argv[1]);
		else
			printf("minishell: cd: %s: No such file or directory\n", minihell->lst_tokens->argv[1]);
		flag = 1;
	}
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
	}
	else
		error_code = 1;
	free(old_pwd);
	free(home);
	free(pwd);
}
