/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:20:48 by jhesso            #+#    #+#             */
/*   Updated: 2023/01/31 17:17:55 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

static int	nlen(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char			*str;
	unsigned int	nbr;
	int				i;

	nbr = n;
	i = nlen(nbr);
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (nbr == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	while (nbr > 0)
	{
		str[i] = '0' + (nbr % 10);
		nbr = nbr / 10;
		i--;
	}
	return (str);
}
