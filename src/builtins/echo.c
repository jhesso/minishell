/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:19:38 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/23 05:26:08 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_line(char **argv, int start)
{
	printf("%s", argv[start]);
	start++;
	while (argv[start])
	{
		printf(" ");
		printf("%s", argv[start]);
		start++;
	}
}

//! changed cmd->argv to cmd->opt as in case of builtins
//! we dont actually make the argv
//! and this was resulting in unknown address error
//! also theres no reason to send the minihell struct here
//! as we only use the cmd (and also needs to be the current cmd in execution)
//! printing is not working but I think thats a problem with piping/duping
void	echo_builtin(t_tokens *cmd)
{
	int	i;
	int	flag;
	int	opt_size;

	i = 0;
	flag = 0;
	opt_size = count_strings(cmd->opt);
	// print_string_arr(cmd->opt); //? why is cmd->opt == path?!?!?!?!
	if (opt_size == 1)
		printf("\n");
	else if (!ft_strncmp(cmd->opt[1], "-n", 2))
	{
		i++;
		while (cmd->opt[1][i] == 'n')
			i++;
		if (cmd->opt[1][i])
			flag = 1;
		if (flag)
		{
			print_line(cmd->opt, 1);
			printf("\n");
		}
		else
			print_line(cmd->opt, 2);
	}
	// else //* if -n is not specified, we dont print anything.. tried adding this but see next comment
	// 	print_line(cmd->opt, 0); //? why is cmd->opt == path?!?!?!?! or at least its printing env
	error_code = 0;
}
