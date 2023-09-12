/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:11:15 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/12 15:15:25 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	get_end_index()
*	get the index of the character after the variable
*	Return value: int (index of the character after the variable)
*	Parameters:
*		char *str: string to get the index from
*		int i: index of the '$' character
*		int type: type of the string
*/
int	get_end_index(char *s, int i, int type)
{
	if (type == 1)
	{
		while (s[i] && !(s[i] > 31 && s[i] < 48) && !(s[i] > 57 && s[i] < 64)
			&& !(s[i] > 90 && s[i] < 97) && !(s[i] > 122 && s[i] < 127))
			i++;
		return (i);
	}
	else if (type == 2)
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		if (s[i])
			i++;
		return (i);
	}
	else if (type == 3)
	{
		while (s[i] && s[i] != '\"')
			i++;
		if (s[i])
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

	if (!value || !str)
		malloc_error();
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
	value = get_value(path, len, envp);
	if (!value)
		return (NULL);
	return (value);
}
