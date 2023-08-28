/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:55:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/28 14:35:14 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_is_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return(0);
}

void	exit_builtin(t_minihell *minihell)
{
	int	i;
	int argv_size;
	int exit_number;

	i = 0;
 	argv_size = count_strings(minihell->lst_tokens->argv);
	if (argv_size == 2 && !arg_is_digit(minihell->lst_tokens->argv[1]))
	{
		// if
		exit_number = ft_atoi(minihell->lst_tokens->argv[1]);
		printf("exit\n");
		if (exit_number > 255)
			error_code = (exit_number - 256);
		error_code = 255;
		if (minihell->nb_cmds == 1)
			exit(error_code);
	}
	else
	{
		printf("ERROR\n");
	}
}
