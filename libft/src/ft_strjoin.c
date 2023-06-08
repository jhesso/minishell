/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:12:58 by jhesso            #+#    #+#             */
/*   Updated: 2023/04/15 17:43:12 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	ft_strjoin()
*	joins given strings s1 and s2 together
*	returns the result as a new string or NULL if malloc failed
*	remember to free all strings after use!
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*ret;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ret = malloc(sizeof(char) * size + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		ret[j++] = s2[i++];
	ret[j] = '\0';
	return (ret);
}
