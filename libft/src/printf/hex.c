/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:38:45 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/14 19:07:19 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/printf.h"

static unsigned int	calculate_hex_digits(unsigned long long nbr)
{
	unsigned int	amount;

	amount = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		amount++;
	}
	return (amount);
}

static char	*convert_to_hex(unsigned long long nbr)
{
	char				*hex_num;
	unsigned long long	decimal;
	int					i;
	int					num_of_digits;

	num_of_digits = calculate_hex_digits(nbr);
	hex_num = malloc(sizeof(char) * (num_of_digits + 1));
	if (hex_num == NULL)
		return (NULL);
	i = 0;
	while (num_of_digits > 0)
	{
		decimal = nbr % 16;
		if (decimal < 10)
			hex_num[i++] = decimal + '0';
		else
			hex_num[i++] = decimal + 87;
		nbr = nbr / 16;
		num_of_digits--;
	}
	hex_num[i] = '\0';
	return (hex_num);
}

int	arg_hex(unsigned long long nbr, char casing)
{
	char	*hex_num;
	int		len;
	int		i;

	hex_num = convert_to_hex(nbr);
	if (hex_num == NULL)
		return (0);
	hex_num = ft_strrev(hex_num);
	i = 0;
	if (casing == 'x')
		len = ft_putstr_fd(hex_num, 1);
	else
	{
		while (hex_num[i])
		{
			if (hex_num[i] >= 'a' && hex_num[i] <= 'f')
				hex_num[i] = ft_toupper(hex_num[i]);
			i++;
		}
		len = ft_putstr_fd(hex_num, 1);
	}
	if (hex_num != NULL)
		free (hex_num);
	return (len);
}
