/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:57:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/14 15:45:20 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* ft_isnum()
*	check that the given string is a number
*	and not more/less than INT_MAX or INT_MIN
*	return: 1 if the string is a number, 0 if not.
*/
int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
