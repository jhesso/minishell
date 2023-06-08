/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:29:39 by jhesso            #+#    #+#             */
/*   Updated: 2022/11/18 10:55:02 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	char	a;

	tmp = (char *)s;
	a = (char)c;
	while (*tmp != '\0')
	{
		if (*tmp == a)
			return ((char *)tmp);
		tmp++;
	}
	if (a == '\0')
	{
		return ((char *)tmp);
	}
	return (NULL);
}
