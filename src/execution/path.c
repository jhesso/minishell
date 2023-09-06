/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:23:18 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 18:55:56 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(char **env)
{
	int     i;
	char    *tmp;
	char    **path;

	i = -1;
	path = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			tmp = ft_strdup(env[i]);
			if (!tmp)
				malloc_error();
			path = ft_split(tmp + 5, ':');
			if (!path)
				malloc_error();
			free(tmp);
			break ;
		}
	}
	return (path);
}

static char *check_valid_path(char *command, char **path)
{
	int     i;
	char    *cmd_path;
	char	*cmd;

	i = 0;
	if (!command[0] || !path)
		return (NULL);
	cmd = ft_strjoin("/", command);
	if (!cmd)
		malloc_error();
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			malloc_error();
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(cmd);
	return (NULL);
}

int    cmd_is_dir(char *cmd)
{
    struct stat    cmd_stat;

    ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
  	stat(cmd, &cmd_stat);
    return (S_ISDIR(cmd_stat.st_mode));
}

void	append_command_path(t_minihell *minihell, t_tokens *lst_tokens)
{
	char		**path;
	char		*cmd;

	path = get_path(minihell->env);
	if (!lst_tokens->command)
		cmd = NULL;
	else
	{
		cmd = ft_strdup(lst_tokens->command);
		if (ft_strchr(cmd, '/'))
		{
			if (access(cmd, F_OK | X_OK) != 0)
			{
				ft_printf(2, "minishell: %s: %s\n", cmd, strerror(errno));
				if (access(cmd, F_OK != 0) && access(cmd, X_OK == 0))
					g_global.error_code = 127;
				else
					g_global.error_code = 126;
				free(lst_tokens->command);
				lst_tokens->command = NULL;
				ft_printf(2, "minishell: %s: No such file or directory\n", cmd);
				g_global.error_code = 127;
			}
			else if (cmd_is_dir(lst_tokens->command))
			{
				free(lst_tokens->command);
				lst_tokens->command = NULL;
				ft_printf(2, "minishell: %s: is a directory\n", cmd);
				g_global.error_code = 126;
			}
		}
		else if (!check_builtin(cmd))
		{
			free(lst_tokens->command);
			lst_tokens->command = check_valid_path(cmd, path);
			if (!lst_tokens->command)
				ft_printf(2, "minishell: %s: command not found\n", cmd);
			g_global.error_code = 127;
		}
		free(cmd);
	}
	if (path)
		free_str_arr(path);
}
