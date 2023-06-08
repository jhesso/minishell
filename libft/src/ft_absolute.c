/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:19:38 by jhesso            #+#    #+#             */
/*   Updated: 2023/02/28 16:23:02 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	ft_absolute()
*	get the absolute number of given integer
*	absolute number = distance from 0
*	-6 = 6
*	-42 = 42
*/
int	ft_absolute(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}
