/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:41:52 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/29 22:24:28 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*	free_str_arr()
*	frees a 2d array of strings (char **)
*	param: char **ret, int row
*	return: NULL (always)
*/
void	*free_str_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	if (s)
		free(s);
	return (NULL);
}

/*	get_value()
*	get the value of the variable
*	Return value: char * (value of the variable)
*	Parameters:
*		char *path: variable with '=' at the end ($USER= for example)
*		int len: length of the variable
*		char **envp: environment variables
*		int i: index of the environment variable
*/
char	*get_value(char *path, int len, char **envp)
{
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], &path[1], len - 1) == 0)
		{
			value = ft_substr(envp[i], len - 1, ft_strlen(envp[i]));
			if (!value)
			{
				free(path);
				return (NULL);
			}
			free(path);
			return (value);
		}
		i++;
	}
	value = ft_calloc(1, 1);
	free(path);
	return (value);
}
