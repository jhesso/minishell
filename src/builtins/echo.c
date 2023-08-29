/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:19:38 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/29 22:32:34 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_line(t_minihell *minihell, int start, int flag)
{
	if (minihell->lst_tokens->argv[start])
	{
		printf("%s", minihell->lst_tokens->argv[start]);
		start++;
	}
	while (minihell->lst_tokens->argv[start])
	{
		printf(" ");
		printf("%s", minihell->lst_tokens->argv[start]);
		start++;
	}
	if (!flag)
		printf("\n");
}

void	echo_builtin(t_minihell *minihell, int j, int flag)
{
	int	i;
	int	argv_size;

	argv_size = count_strings(minihell->lst_tokens->argv);
	if (argv_size == 1)
		printf("\n");
	else if (argv_size > 1)
	{
		while (!ft_strncmp(minihell->lst_tokens->argv[j], "-n", 2))
		{
			i = 1;
			while (minihell->lst_tokens->argv[j][i] == 'n')
				i++;
			if (j == 1 && !minihell->lst_tokens->argv[j][i])
				flag = 1;
			else if (minihell->lst_tokens->argv[j][i] != '\0')
				break ;
			j++;
		}
		if (!flag)
			print_line(minihell, 1, flag);
		else
			print_line(minihell, j, flag);
	}
	error_code = 0;
}
