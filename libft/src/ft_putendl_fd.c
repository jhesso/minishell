/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:23:35 by jhesso            #+#    #+#             */
/*   Updated: 2022/12/12 22:00:29 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	ret = 0;
	if (s != NULL)
		ret = ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	ret++;
	return (ret);
}
