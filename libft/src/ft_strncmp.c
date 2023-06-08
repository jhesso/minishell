/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:30:15 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/22 16:16:57 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	ft_strcmp()
*	compares the first n amount of characters of s1 and s2
*	returns: an integer indicating the result of the comparison, as follows:
*	- 0, if the s1 and s2 are equal
*	- a negative value if s1 is less than s2
*	- a positive value if s1 is greated than s2
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
