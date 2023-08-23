/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 04:47:46 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 15:57:49 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_minihell *minihell, int builtin)
{
	if (builtin == 1)
		echo_builtin(minihell);
	// else if (builtin == 2)
	// 	cd_builtin(minihell);
	else if (builtin == 3)
		pwd_builtin();
	else if (builtin == 4)
		export_builtin(minihell);
	// else if (builtin == 5)
	// 	unset_builtin(minihell);
	else if (builtin == 6)
		env_builtin(minihell);
	// else if (builtin == 7)
	// 	exit_builtin(minihell);
}
