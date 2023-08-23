/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:41:52 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 03:55:29 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*	free_str_arr()
*	frees a 2d array of strings (char **)
*	param: char **ret, int row
*	return: NULL (always)
*/
void	*free_str_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	if (s)
		free(s);
	return (NULL);
}
