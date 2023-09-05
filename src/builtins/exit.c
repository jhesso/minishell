/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:55:01 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/05 12:47:55 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	overflows(long long int number, char *arg, bool *error)
{
	if (arg[0] == '-' && number == 0
		&& ft_strncmp(arg, "-9223372036854775808\0", 21))
		*error = false;
	else if (arg[0] != '-'
		&& number == -1 && ft_strncmp(arg, "9223372036854775807\0", 20))
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
	return (0);
}

static void	exit_checks(t_minihell *minihell, int argv_size, int number, bool *error)
{
	if (argv_size == 2 && error && !arg_is_digit(minihell->lst_tokens->argv[1]))
	{
		global.error_code = number % 256;
		exit(global.error_code);
	}
	else if (argv_size >= 2 && (!error || arg_is_digit(minihell->lst_tokens->argv[1])))
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n", minihell->lst_tokens->argv[1]);
		global.error_code = 255;
		exit(global.error_code);
	}
	else if (argv_size >= 2)
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		global.error_code = 1;
	}
	else
	{
		global.error_code = 0;
		exit(global.error_code);
	}
}

void	exit_builtin(t_minihell *minihell)
{
	bool		error;
	int			argv_size;
	long int	number;

	error = true;
	argv_size = count_strings(minihell->lst_tokens->argv);
	number = 0;
	if (minihell->nb_cmds == 1)
		printf("exit\n");
	if (argv_size >= 2)
	{
		number = ft_atoi(minihell->lst_tokens->argv[1]);
		overflows(number, minihell->lst_tokens->argv[1], &error);
	}
	exit_checks(minihell, argv_size, number, &error);
}
