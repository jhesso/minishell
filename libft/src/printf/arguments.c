/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:43:54 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/31 17:38:56 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

int	arg_str(char *str, int fd)
{
	int	len;

	if (str == NULL)
		return (ft_putstr_fd("(null)", fd));
	len = ft_putstr_fd(str, fd);
	return (len);
}

int	arg_int(int nbr, int fd)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_putstr_fd(str, fd);
	if (str != NULL)
		free(str);
	return (len);
}

int	arg_unsigned_int(unsigned int nbr, int fd)
{
	char	*str;
	int		len;

	str = ft_itoa_unsigned(nbr);
	len = ft_putstr_fd(str, fd);
	if (str != NULL)
		free(str);
	return (len);
}
