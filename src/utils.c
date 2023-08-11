/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:41:52 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/11 17:59:46 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	free_str_arr()
*	frees a 2d array of strings (char **)
*	param: char **ret, int row
*	return: NULL (always)
*/
char	**free_str_arr(char **ret, int row)
{
	while (row >= 0) //? why not return starting from the first row until we reach NULL?
		free(ret[row--]);
	free(ret);
	return (NULL);
}
