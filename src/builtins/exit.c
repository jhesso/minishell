/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:55:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/28 19:06:11 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	overflows(long long int number, char *arg, bool *error)
{
	if (arg[0] == '-' && number == 0 && ft_strncmp(arg, "-9223372036854775808\0", 21))
		*error = false;
	else if (arg[0] != '-' && number == -1 && ft_strncmp(arg, "9223372036854775807\0", 20))
		*error = false;
}

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

void exit_minishell(t_minihell *minihell)
{
	if (minihell->nb_cmds == 1)
		exit(error_code);
}

void	exit_builtin(t_minihell *minihell)
{
	bool				error;
	int 				argv_size;
	long int			number;
	unsigned long long 	exit_number;

	error = true;
 	argv_size = count_strings(minihell->lst_tokens->argv);
	number = 0;
	exit_number = 0;
	if (argv_size >= 2)
	{
		if (minihell->nb_cmds == 1)
			printf("exit\n");
		number = ft_atoi(minihell->lst_tokens->argv[1]);
		overflows(number, minihell->lst_tokens->argv[1], &error);
	}
	if (argv_size == 2 && error && !arg_is_digit(minihell->lst_tokens->argv[1]))
	{
		error_code = number % 256;
		exit_minishell(minihell);
	}
	else if (argv_size >= 2 && (!error || arg_is_digit(minihell->lst_tokens->argv[1])))
	{
		printf("minishell: exit: %s: numeric argument required\n", minihell->lst_tokens->argv[1]);
		error_code = 255;
		exit_minishell(minihell);
	}
	else if (argv_size >= 2)
	{
		printf("minishell: exit: too many arguments\n");
		error_code = 1;
	}
	else if (minihell->nb_cmds == 1)
		exit(0);
}