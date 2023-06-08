/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:07:54 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/22 04:07:07 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	ft_substr()
*	creates a substring from the string s, starting from the index start
*	the substr is at max len characters long
*	neither the string s or the created substr are freed, so the caller needs
*	to deal with that
*	returns: the string created if all good, NULL if failed
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start == 0 || start > ft_strlen(s))
	{
		if (start > ft_strlen(s))
			len = 0;
		if (len > ft_strlen(s))
			len = ft_strlen(s);
	}
	substr = malloc(sizeof(char) * len + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
