/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_digits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:49:25 by jhesso            #+#    #+#             */
/*   Updated: 2023/01/31 18:06:41 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	ft_calculate_digits()
*	Takes an unsigned long integer and calculates how many digits it has
*	useful for itoa and similar functions that need to allocate memory for
*	a string that contains an int
*/
long	ft_calculate_digits(unsigned long int nbr)
{
	long	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}
