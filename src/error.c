/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:04:47 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/06 18:59:55 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	ft_printf(2, "Error: Malloc Error!");
	exit(1);
}

void	dup_error(void)
{
	ft_printf(2, "Error: Dup failed!");
	exit(1);
}
