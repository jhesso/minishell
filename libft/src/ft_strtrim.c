/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:18:01 by jhesso            #+#    #+#             */
/*   Updated: 2022/11/18 10:55:02 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	find_start(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	match;

	i = 0;
	match = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] != set[j] && j == (int)ft_strlen(set) - 1)
				match = 1;
			else if (s1[i] == set[j])
				break ;
			j++;
		}
		if (match == 1)
			break ;
		i++;
	}
	return (i);
}

static int	find_end(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	match;

	i = (int)ft_strlen(s1) - 1;
	match = 0;
	while (i >= 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] != set[j] && j == (int)ft_strlen(set) - 1)
				match = 1;
			else if (s1[i] == set[j])
				break ;
			j++;
		}
		if (match == 1)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ret;
	int		start;
	int		end;
	int		size;
	int		i;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL || set[0] == '\0')
		return (ft_strdup(s1));
	start = find_start(s1, set);
	end = find_end(s1, set);
	size = (int)ft_strlen(s1);
	size = size - ((int)ft_strlen(s1) - (end + 1)) - start;
	if (size < 0)
		size = 0;
	ret = malloc(sizeof(char) * size + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		ret[i++] = s1[start++];
	ret[i] = '\0';
	return (ret);
}
