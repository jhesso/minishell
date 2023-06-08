/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:47:34 by jhesso            #+#    #+#             */
/*   Updated: 2022/11/18 10:55:02 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const char	*src_cpy;
	char		*dst_cpy;
	size_t		dst_len;
	size_t		i;
	size_t		src_len;

	src_cpy = src;
	dst_cpy = dst;
	if (dst_cpy == NULL && dstsize == 0)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len > dstsize)
		return (dstsize + src_len);
	i = 0;
	while (dst_cpy[i] != '\0')
		i++;
	while (*src_cpy != '\0' && i < dstsize - 1 && dstsize != 0)
	{
		dst_cpy[i] = *src_cpy;
		i++;
		src_cpy++;
	}
	dst_cpy[i] = '\0';
	return (dst_len + src_len);
}
