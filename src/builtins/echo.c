/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:19:38 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/23 15:37:55 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_line(t_minihell *minihell, int start)
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
 }

 void	echo_builtin(t_minihell *minihell)
 {
 	int	i;
 	int	flag;
 	int	argv_size;

 	i = 0;
 	flag = 0;
 	argv_size = count_strings(minihell->lst_tokens->argv);
 	if (argv_size == 1)
 		printf("\n");
 	else if (!ft_strncmp(minihell->lst_tokens->argv[1], "-n", 2))
 	{
 		i++;
 		while (minihell->lst_tokens->argv[1][i] == 'n')
 			i++;
 		if (minihell->lst_tokens->argv[1][i])
 			flag = 1;
 		if (flag)
 		{
 			print_line(minihell, 1);
 			printf("\n");
 		}
 		else
 			print_line(minihell, 2);
 	}
	else
	{
		print_line(minihell, 1);
 		printf("\n");
	}
 	error_code = 0;
 }
