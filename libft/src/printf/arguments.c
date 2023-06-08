/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:43:54 by jhesso            #+#    #+#             */
/*   Updated: 2023/01/31 17:17:36 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

int	arg_str(char *str)
{
	int	len;

	if (str == NULL)
		return (ft_putstr_fd("(null)", 1));
	len = ft_putstr_fd(str, 1);
	return (len);
}

int	arg_int(int nbr)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_putstr_fd(str, 1);
	if (str != NULL)
		free(str);
	return (len);
}

int	arg_unsigned_int(unsigned int nbr)
{
	char	*str;
	int		len;

	str = ft_itoa_unsigned(nbr);
	len = ft_putstr_fd(str, 1);
	if (str != NULL)
		free(str);
	return (len);
}
