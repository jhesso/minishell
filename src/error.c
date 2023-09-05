/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:04:47 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/05 14:12:26 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	// ft_putstr_fd(strerror(errno), 2);
	ft_printf(2, "Error: Malloc Error!");
	exit(12); //! probably not the right way to exit, but it works for now
	//? error code 12!!!!!
}

void	dup_error(void)
{
	// ft_putstr_fd(strerror(errno), 2);
	ft_printf(2, "Error: Dup failed!");
	exit(12); //! probably not the right way to exit, but it works for now
	//? error code 12!!!!!
}
