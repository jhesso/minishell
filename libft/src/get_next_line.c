/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:24:19 by jhesso            #+#    #+#             */
/*   Updated: 2022/12/02 16:14:50 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_join(char *stash, char *buffer)
{
	char	*new_stash;

	new_stash = ft_strjoin(stash, buffer);
	free(stash);
	return (new_stash);
}

static char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		ret;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL || stash == NULL)
		return (NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = 0;
		stash = ft_join(stash, buffer);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free (buffer);
	return (stash);
}

static char	*ft_find_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*ft_truncate_stash(char *stash)
{
	char	*n_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	n_stash = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	if (n_stash == NULL)
		return (NULL);
	j = 0;
	i++;
	while (stash[i])
	{
		n_stash[j] = stash[i];
		i++;
		j++;
	}
	free(stash);
	return (n_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_find_line(stash);
	stash = ft_truncate_stash(stash);
	return (line);
}
