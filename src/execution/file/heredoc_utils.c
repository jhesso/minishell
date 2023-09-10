/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:15:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/10 14:27:50 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		printf("\033[1A");
		g_global.heredoc_signal = false;
	}
	else
		g_global.heredoc_signal = true;
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

char	*get_num(char *name, int cmd)
{
	char	*nb;
	char	*tmp;

	nb = ft_itoa(cmd);
	tmp = ft_strjoin(name, nb);
	if (!tmp)
		return (NULL);
	while (access(tmp, F_OK) == 0)
	{
		free(nb);
		free(tmp);
		cmd++;
		nb = ft_itoa(cmd);
		tmp = ft_strjoin(name, nb);
		if (!tmp)
			return (NULL);
	}
	free(tmp);
	return (nb);
}
