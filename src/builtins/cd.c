/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:11:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/13 23:05:59 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	int		size;
	char	*ret;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ret = malloc(sizeof(char) * size + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		ret[j++] = s2[i++];
	ret[j] = '\0';
	free(s2);
	return (ret);
}

static void	modify_env(t_minihell *mini, char *old_pwd, char *home, int flag)
{
	char	*pwd;

	pwd = ft_strjoin_free("PWD=", getcwd(NULL, 0));
	if (!pwd)
		malloc_error();
	if (!flag)
	{
		if (already_exists(mini, old_pwd, 0, 0))
			mini->env = export_variable(mini->env, old_pwd);
		if (already_exists(mini, pwd, 0, 0))
			mini->env = export_variable(mini->env, pwd);
		mini->error_code = 0;
	}
	else
		mini->error_code = 1;
	free(old_pwd);
	free(home);
	free(pwd);
}

void	cd_builtin(t_minihell *mini, char *old_pwd, char *home, int flag)
{
	old_pwd = ft_strjoin_free("OLDPWD=", \
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
	else if (mini->cmds->argv[1][0] && chdir(mini->cmds->argv[1]))
	{
		ft_printf(2, "minishell: cd: %s: %s\n", \
			mini->cmds->argv[1], strerror(errno));
		flag = 1;
	}
	modify_env(mini, old_pwd, home, flag);
}
