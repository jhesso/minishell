/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:55:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/25 21:45:17 by dgerguri         ###   ########.fr       */
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
		exit_number = ft_atoi(minihell->lst_tokens->argv[1]);
		if (exit_number > 255)
			exit (exit_number - 256);
		printf("IT IS A NUMBER\n");
	}
	else
	{
		printf("ERROR\n");
	}
}
