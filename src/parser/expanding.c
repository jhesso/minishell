/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:45:20 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/24 23:57:30 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	get_end_index()
*	get the index of the character after the variable
*	Return value: int (index of the character after the variable)
*	Parameters:
*		char *str: string to get the index from
*		int i: index of the '$' character
*		int type: type of the string (1 = normal, 2 = single quotes, 3 = double quotes)
*/
int	get_end_index(char *str, int i, int type)
{
	if (type == 1)
	{
		while (str[i] && str[i] != '\'' && str[i] != '\"'
			&& str[i] != '$' && str[i] != ' ' && str[i] != '=')
			i++;
		return (i);
	}
	else if (type == 2)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i])
			i++;
		return (i);
	}
	else if (type == 3)
	{
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i])
			i++;
		return (i);
	}
	return (0);
}

/*	insert_value()
*	insert the value of the variable in to the string
*	Return value: char * (new string)
*	Parameters:
*		char *str: string to insert the value in to
*		char *value: value of the variable
*		int start: index of the '$' character
*		int new_start: index of the character after the variable
*/
char	*insert_value(char *str, char *value, int start, int new_start)
{
	char	*new_str;
	int		value_len;
	int		new_str_len;

	value_len = ft_strlen(value);
	new_str_len = ft_strlen(str) + value_len + 1;
	new_str = malloc(sizeof(char) * (new_str_len));
	if (new_str == NULL)
	{
		free(value);
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, new_str_len);
	ft_strlcpy(new_str + start, value, new_str_len);
	ft_strlcpy(new_str + start + value_len, str + new_start, new_str_len);
	free(value);
	return (new_str);
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
char	*get_value(char *path, int len, char **envp, int i)
{
	char	*value;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], &path[1], len - 1) == 0) //? why $path[1]?
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

/*	expand()
*	expand the variable
*	Return value: char * (value of the variable)
*	Parameters:
*		char *str: string to expand
*		char **envp: environment variables
*		int start: index of the '$' character
*		int end: index of the character after the variable
*/
char	*expand(char *str, char **envp, int start, int end)
{
	char	*sub_path;
	char	*value;
	char	*path;
	int		len;

	sub_path = ft_substr(str, start, end - start);
	if (!sub_path)
		return (NULL);
	path = ft_strjoin(sub_path, "=");
	if (!path)
	{
		free(sub_path);
		return (NULL);
	}
	free(sub_path);
	len = ft_strlen(path);
	value = get_value(path, len, envp, 0);
	if (!value)
		return (NULL);
	return (value);
}

/*	expand_str()
*	do the actual expanding (replace the variable with its value)
*	Return value: char * (expanded string)
*	Parameters:
*		char *str: string to expand
*		char **envp: environment variables
*		int s: index of the '$' character
*/
char	*expand_str(char *str, char **envp, int s)
{
	char	*new_str;
	char	*value;
	int		end;

	if (str[s + 1] == '\0' || str[s + 1] == '\'' || str[s + 1] == '\"')
	{
		new_str = insert_value(str, (char *)ft_calloc(1, 1), s, s + 1);
		if (!new_str)
			return (NULL);
	}
	else if (str[s + 1] == '?')
		new_str = insert_value(str, ft_itoa(error_code), s, s + 2);
	else
	{
		end = get_end_index(str, s + 1, 1);
		value = expand(str, envp, s, end);
		if (!value)
		{
			free(str);
			return (NULL);
		}
		new_str = insert_value(str, value, s, end);
		if (!new_str)
			return (NULL);
	}
	free(str);
	return (new_str);
}

/*	expand_quotes()
*	expand variables inside double quotes
*	Return value: char * (expanded string)
*	Parameters:
*		char *str: string to expand
*		char **envp: environment variables
*		int start: index of the first quote
*/
char	*expand_quotes(char *str, char **envp, int start)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	start++;
	while (new_str[start] && new_str[start] != '\"')
	{
		if (new_str[start] == '$')
		{
			new_str = expand_str(new_str, envp, start);
			if (!new_str)
			{
				free(str);
				return (NULL);
			}
		}
		start++;
	}
	free(str);
	return (new_str);
}

/*	expand_variables()
*	expand environment variables
*	Return value: char * (expanded string)
*	Parameters:
*		char *str: string to expand
*		char **envp: environment variables
*/
char	*expand_variables(char *str, char **envp)
{
	int	start;

	start = 0;
	while (str[start])
	{
		if (str[start] == '$')
		{
			str = expand_str(str, envp, start);
			if (!str)
				return (NULL);
		}
		else if (str[start] == '\"')
		{
			start++;
			str = expand_quotes(str, envp, start - 1);
			if (!str)
				return (NULL);
			start = get_end_index(str, start, 3);
		}
		else if (str[start] == '\'')
			start = get_end_index(str, start, 2);
		else
			start++;
	}
	return (str);
}
