/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:11:39 by jhesso            #+#    #+#             */
/*   Updated: 2023/04/15 17:43:24 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	ft_strdup()
*	copies given string s1 into a new string
*	returns the copy of string s1 or NULL if malloc failed
*	remember to free both strings after use!
*/
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char) * ft_strlen((char *) s1) + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
