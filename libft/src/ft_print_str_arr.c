/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:08:12 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/01 15:28:45 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	print_string_arr()
*	prints out the contents of char **arr
*	It is assumed that the char ** is NULL terminated
*/
void	print_string_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_printf(1, "%s\n", arr[i]);
		i++;
	}
}
