/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:45:20 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/24 23:09:19 by jhesso           ###   ########.fr       */
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
	if (type == 1) //* for "normal" variables
	{
		while (str[i] && str[i] != '\'' && str[i] != '\"'
			&& str[i] != '$' && str[i] != ' ' && str[i] != '=') //* skip the string until we find a character that ends the variable
			i++;
		return (i);
	}
	else if (type == 2) //* if the string is in single quotes
	{
		i++;
		while (str[i] && str[i] != '\'') //* skip the string until we find the closing quote (or '\0')
			i++;
		if (str[i]) //* if we found the closing quote, skip it
			i++;
		return (i);
	}
	else if (type == 3) //* if the string is in double quotes
	{
		while (str[i] && str[i] != '\"') //* skip the string until we find the closing quote (or '\0')
			i++;
		if (str[i]) //* if we found the closing quote, skip it
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

	value_len = ft_strlen(value); //* get the length of the value (in case of $"", it will be 0)
	new_str_len = ft_strlen(str) + value_len + 1; //* calculate the length of the new string (original string + value + '\0')
	new_str = malloc(sizeof(char) * (new_str_len));
	if (new_str == NULL)
	{
		free(value);
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, new_str_len); //* copy the original string to the new string
	ft_strlcpy(new_str + start, value, new_str_len); //* replace the variable with its value
	ft_strlcpy(new_str + start + value_len, str + new_start, new_str_len); //* copy the rest of the string
	free(value); //* free the value since we are returning the new string
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

	while (envp[i]) //* loop through the environment variables
	{
		if (ft_strncmp(envp[i], &path[1], len - 1) == 0) //? why $path[1]?
		{
			value = ft_substr(envp[i], len - 1, ft_strlen(envp[i])); //* create a substring of the value
			if (!value)
			{
				free(path);
				return (NULL);
			}
			free(path); //* free the path since we are returning the value
			return (value);
		}
		i++;
	}
	value = ft_calloc(1, 1); //* if the variable doesn't exist, return an empty string
	free(path); //* free the path since we are returning the value
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
	char	*sub_path; //* substring of the variable ($USER for example)
	char	*value; //* value of the variable
	char	*path; //* variable with '=' at the end ($USER= for example) | I'd call this var_name or smth | freed in get_value()
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
	free(sub_path); //* free the substring since we dont need it anymore
	len = ft_strlen(path);
	value = get_value(path, len, envp, 0); //* get the value of the variable
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
	char	*value; //* value of the variable | freed in insert_value()
	int		end;

	if (str[s + 1] == '\0' || str[s + 1] == '\'' || str[s + 1] == '\"') //* if str ends with a $ or the next character is a quote
	{
		new_str = insert_value(str, (char *)ft_calloc(1, 1), s, s + 1); //* insert an empty string
		if (!new_str)
			return (NULL);
	}
	else if (str[s + 1] == '?') //* if the next character is '?' (error code)
		new_str = insert_value(str, ft_itoa(error_code), s, s + 2); //* convert error_code to string and insert it
	else
	{
		end = get_end_index(str, s + 1, 1); //* get the index of the character after the variable
		value = expand(str, envp, s, end); //* expand the variable
		if (!value)
		{
			free(str);
			return (NULL);
		}
		new_str = insert_value(str, value, s, end); //* insert the value of the variable
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

	new_str = ft_strdup(str); //* duplicate the string
	if (!new_str)
		return (NULL);
	start++; //* skip the first quote
	while (new_str[start] && new_str[start] != '\"')
	{
		if (new_str[start] == '$') //* look for the '$' character
		{
			new_str = expand_str(new_str, envp, start); //* expand the string from the '$' character
			if (!new_str)
			{
				free(str);
				return (NULL);
			}
		} //? couldn't we break here since the string is expanded? is this incase the quotes contain multiple variables?
		start++;
	}
	free(str); //* free the original string since we are returning the expanded string and replacing the original with that
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
	int	start; //* keep track of the index we are at

	start = 0;
	while (str[start])
	{
		if (str[start] == '$') //* if we find an unquoted $, expand it
		{
			str = expand_str(str, envp, start);
			if (!str)
				return (NULL);
		}
		else if (str[start] == '\"') //* if the string is in double quotes
		{
			start++; //* skip the first quote
			str = expand_quotes(str, envp, start - 1); //* expand the string | Why the fuck do we increment start just to send start - 1 here?!
			if (!str)
				return (NULL);
			start = get_end_index(str, start, 3); //* skip the expanded string
		}
		else if (str[start] == '\'') //* if the string is in single quotes
			start = get_end_index(str, start, 2); //* skip the string
		else
			start++;
	}
	return (str); //* return the expanded string (or the original if no variables present (or they are in single quotes))
}

/*	parse_str()
*	expand environment variables and remove extra quotes
*	Return value: char * (modified string)
*	Parameters:
*		int c: index of the string we are modifying
*		t_minihell *minihell: our minihell struct containing the strings to be modified
*/
char    *parse_str(int c, t_minihell *minihell)
{
	if (!ft_strncmp(minihell->tokens[c - 1], "<<\0", 3))
    	minihell->tokens[c] = expand_variables(minihell->tokens[c], minihell->env); //* expand variables
    if (!minihell->tokens[c]) //* check for malloc errors
        malloc_error();
    minihell->tokens[c] = remove_quotes(minihell->tokens[c], 0, 0); //* remove quotes
    return (ft_strdup(minihell->tokens[c])); //* return a duplicate of the parsed string (so we can free it in the list and in the tokens** array)
}
