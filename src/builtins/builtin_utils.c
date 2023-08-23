/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:19:14 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 04:45:56 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *cmd)
{ //? why not just return 1, 2, 3, etc..?
	int	i;

	i = 0;
	if (!ft_strncmp(cmd, "echo\0", 5))
		i = 1;
	else if (!ft_strncmp(cmd, "cd\0", 3))
		i = 2;
	else if (!ft_strncmp(cmd, "pwd\0", 4))
		i = 3;
	else if (!ft_strncmp(cmd, "export\0", 7))
		i = 4;
	else if (!ft_strncmp(cmd, "unset\0", 6))
		i = 5;
	else if (!ft_strncmp(cmd, "env\0", 4))
		i = 6;
	else if (!ft_strncmp(cmd, "exit\0", 5))
		i = 7;
	else
		i = 0;
	return (i);
}
