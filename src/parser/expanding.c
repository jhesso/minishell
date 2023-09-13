/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:45:20 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/13 15:42:24 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expand_char(char *str, int start, int type)
{
	if (type == 1)
	{
		if (str[start + 1] && !(str[start + 1] > 31 && str[start + 1] < 34) \
			&& !(str[start + 1] > 34 && str[start + 1] < 39) \
			&& !(str[start + 1] > 39 && str[start + 1] < 48) \
			&& !(str[start + 1] > 57 && str[start + 1] < 63) \
			&& !(str[start + 1] > 90 && str[start + 1] < 97) \
			&& !(str[start + 1] > 122 && str[start + 1] < 127) \
			&& str[start + 1] != 64)
			return (0);
	}
	else if (type == 2 && str[start + 1])
	{
		if (!(str[start + 1] > 31 && str[start + 1] < 48) \
			&& !(str[start + 1] > 57 && str[start + 1] < 63) \
			&& !(str[start + 1] > 90 && str[start + 1] < 97) \
			&& !(str[start + 1] > 122 && str[start + 1] < 127) \
			&& str[start + 1] != 64)
			return (0);
	}
	return (1);
}

static char	*expand_str_continue(char *str, char **envp, int s)
{
	char	*value;
	char	*new_str;
	int		end;

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
	return (new_str);
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

	if (str[s + 1] == '\'' || str[s + 1] == '\"')
	{
		new_str = insert_value(str, (char *)ft_calloc(1, 1), s, s + 1);
		if (!new_str)
			return (NULL);
	}
	else if (!str[s + 1])
	{
		new_str = ft_strdup("$");
		if (!new_str)
			malloc_error();
	}
	else if (str[s + 1] == '?')
		new_str = insert_value(str, ft_itoa(g_global.error_code), s, s + 2);
	else
		new_str = expand_str_continue(str, envp, s);
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
		if (new_str[start] == '$' && !handle_expand_char(new_str, start, 2))
		{
			new_str = expand_str(new_str, envp, start);
			if (!new_str)
			{
				free(str);
				return (NULL);
			}
		}
		if (new_str[1] != '$' || handle_expand_char(new_str, 1, 2))
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
		if (str[start] == '$' && !handle_expand_char(str, start, 1))
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
