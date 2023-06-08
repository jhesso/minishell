/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:21:27 by jhesso            #+#    #+#             */
/*   Updated: 2022/12/12 21:55:55 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	ret;
	int	len;

	ret = 0;
	if (s != NULL)
	{
		len = ft_strlen(s);
		ret = write(fd, s, len);
	}
	return (ret);
}
