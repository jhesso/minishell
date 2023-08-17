/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/17 15:29:19 by dgerguri         ###   ########.fr       */
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

char *check_valid_path(char *command, char **path)
{
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

void append_commands(t_minihell *minihell)
{
	char		**path;
	char		*cmd;
	t_tokens	*tmp;

	tmp = minihell->lst_tokens;
	path = get_path(minihell->env);
	while (minihell->lst_tokens != NULL)
	{
		cmd = ft_strdup(minihell->lst_tokens->command);
		if (ft_strchr(cmd, '/'))
		{
			if (access(cmd, F_OK | X_OK) != 0)
			{
				free(minihell->lst_tokens->command);
				minihell->lst_tokens->command = NULL;
				printf("bash: %s: No such file or directory\n", cmd);
			}
		}
		else// if (!is_builtin) //will have to create a function!!
		{
			free(minihell->lst_tokens->command);
			minihell->lst_tokens->command = check_valid_path(cmd, path);
			if (!minihell->lst_tokens->command)
				printf("bash: %s: command not found\n", cmd);
		}
		free(cmd);
    	minihell->lst_tokens = minihell->lst_tokens->next;
	}
	free_str_arr(path);
	minihell->lst_tokens = tmp;
}

void	create_argv(t_minihell *minihell)
{
	t_tokens	*temp;
	int			options;
	int			i;

	temp = minihell->lst_tokens;
	while (minihell->lst_tokens != NULL)
	{
		options = count_strings(minihell->lst_tokens->opt);
		minihell->lst_tokens->argv = malloc(sizeof(char *) * (options + 2));
		if (!minihell->lst_tokens->argv)
			malloc_error();
		minihell->lst_tokens->argv[0] = ft_strdup(minihell->lst_tokens->command);
		if (!minihell->lst_tokens->argv[0])
			malloc_error();
		i = 0;
		while (minihell->lst_tokens->opt[i])
		{
			minihell->lst_tokens->argv[i + 1] = minihell->lst_tokens->opt[i];
			i++;
		}
		minihell->lst_tokens->argv[i + 1] = NULL;
    	minihell->lst_tokens = minihell->lst_tokens->next;
	}
	minihell->lst_tokens = temp;
}

bool	execute(t_minihell *minihell)
{
	create_argv(minihell);
	open_files(minihell->lst_tokens);
	append_commands(minihell);
	return (true);
}
