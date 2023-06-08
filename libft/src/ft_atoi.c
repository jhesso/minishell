/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:10:59 by jhesso            #+#    #+#             */
/*   Updated: 2022/11/10 15:01:23 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long int	n;
	long int	sign;

	sign = 1;
	n = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
		if (n < 0)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return ((int)n * (int)sign);
}
