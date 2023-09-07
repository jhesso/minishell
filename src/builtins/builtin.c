/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 04:47:46 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/07 14:41:28 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_minihell *minihell, int builtin)
{
	if (builtin == 1)
		echo_builtin(minihell, 1, 0, 0);
	else if (builtin == 2)
		cd_builtin(minihell, NULL, NULL, 0);
	else if (builtin == 3)
		pwd_builtin(minihell);
	else if (builtin == 4)
		export_builtin(minihell, 0, 0);
	else if (builtin == 5)
		unset_builtin(minihell);
	else if (builtin == 6)
		env_builtin(minihell);
	else if (builtin == 7)
		exit_builtin(minihell);
}
