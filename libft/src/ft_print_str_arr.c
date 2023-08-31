/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:08:12 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/31 23:37:31 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	print_string_arr()
*	prints out the contents of char **arr
*	It is assumed that the char ** is NULL terminated
*/
void	print_string_arr(char **arr, int fd)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_printf(fd, "%s\n", arr[i]);
		i++;
	}
}
