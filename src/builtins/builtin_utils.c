/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:19:14 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/28 14:26:19 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo\0", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd\0", 3))
		return (2);
	else if (!ft_strncmp(cmd, "pwd\0", 4))
		return (3);
	else if (!ft_strncmp(cmd, "export\0", 7))
		return (4);
	else if (!ft_strncmp(cmd, "unset\0", 6))
		return (5);
	else if (!ft_strncmp(cmd, "env\0", 4))
		return (6);
	else if (!ft_strncmp(cmd, "exit\0", 5))
		return (7);
	else
		return(0);
	return (i);
}

int	invalid_variable(char *arg, int type)
{
		if (type == 1)
			printf("minishell: export: `%s': not a valid identifier\n", arg);
		if (type == 2)
			printf("minishell: unset: `%s': not a valid identifier\n", arg);
		error_code = 1;
		return (1);//error_code);
}
