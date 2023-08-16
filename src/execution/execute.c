/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/16 15:47:58 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
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
				return (NULL);
			path = ft_split(tmp + 5, ':');
			if (!path)
			{
				free(tmp);
				return(NULL);
			}
			free(tmp);
			break ;
		}
	}
	return (path);
}

char *check_valid_path(char *command, char **path)
{
	// printf("command: %s\n", command);
	int     i;
	char    *cmd_path;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", command);
	if (!cmd)
		malloc_error();
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			malloc_error();
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void append_commands(t_minihell *minihell)
{
	char	**path;
	char	*cmd;
	char	*cmd_path;

	path = get_path(minihell->env);
	if (!path)
    	malloc_error();
	while (minihell->lst_tokens != NULL)
	{
		cmd = minihell->lst_tokens->command;
		if (ft_strchr(cmd, '/'))
		{
			if (access(cmd, F_OK | X_OK) != 0)
				printf("bash: %s: No such file or directory\n", cmd);
		}
		else
		{
			cmd_path = check_valid_path(cmd, path);
			if (!cmd_path)
				printf("bash: %s: command not found\n", cmd);
			free(cmd_path);
		}
    	minihell->lst_tokens = minihell->lst_tokens->next;
	}
	free_str_arr(path);
}

bool	execute(t_minihell *minihell)
{
	(void)minihell;
	// open_files(minihell);
	// check_builtin(minihell);
	append_commands(minihell); // dardan has this basically done
	return (true);
}
