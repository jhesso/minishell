/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:16:24 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/09 22:54:01 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_global.error_code == 256 || g_global.error_code == 386)
			g_global.error_code = 386;
		else
		{
			printf("\n");
			g_global.error_code = 1;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void)sig;
		return ;
	}
}

void	handle_cmd(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		(void)sig;
	}
	else if (sig == SIGQUIT)
		printf("Quit: %d\n", sig);
	return ;
}
