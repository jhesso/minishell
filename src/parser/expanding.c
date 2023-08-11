/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:45:20 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/11 14:49:27 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_index(char *str, int i, int type)
{
	if (type == 1)
	{
		i++;
		while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
			i++;
		return (i);
	}
	if (type == 2)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i])
		i++;
		return (i);
	}
	if (type == 3)
	{
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i])
			i++;
		return (i);
	}
	return (0);
}

char	*insert_value(char *str, char *value, int start, int new_start)
{
	char	*new_str;
	int		value_len;
	int		new_str_len;
	int		i;

	value_len = ft_strlen(value);
	new_str_len = ft_strlen(str) + value_len + 1;
	i = 0;
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

char	*get_value(char *path, int len, char **envp, int i)
{
	char	*value;

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

char	*expand_str(char *str, char **envp, int start)
{
	char	*new_str;
	char	*value;
	int		end;

	if (str[start + 1] == '\0' || str[start + 1] == '\'' || str[start + 1] == '\"')
	{
		new_str = insert_value(str, (char *)ft_calloc(1, 1), start, start + 1);
		if (!new_str)
			return (NULL);
	}
	else
	{
		end = get_end_index(str, start, 1);
		value = expand(str, envp, start, end);
		if (!value)
		{
			free(str);
			return (NULL);
		}
		new_str = insert_value(str, value, start, end);
		if (!new_str)
			return (NULL);
	}
	free(str);
	return (new_str);
}

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
			break ;
		}
		start++;
	}
	free(str);
	return (new_str);
}

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

char	*parse_str(char *str, t_minihell *minihell)
{
	char	*ret;

	ret = expand_variables(str, minihell->env);
	if (!ret)
	{
		malloc_error();
		return (NULL); //make sure that it is freeing the char ** WE CAN MAKE MALLOC RETURN NULL AND WE CAN ONLY HAVE ONE LINE
	}
	//free the remaining char**
	ret = remove_quotes(ret, 0, 0);
	return (ret);
}
