/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:06:30 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/22 16:15:30 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	ft_strcmp()
*	compares the two strings s1 and s2
*	returns: an integer indicating the result of the comparison, as follows:
*	- 0, if the s1 and s2 are equal
*	- a negative value id s1 is less than s2
*	- a positive value if s1 is greated than s2
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
