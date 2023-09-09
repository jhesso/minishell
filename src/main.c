/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/09 22:53:43 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_eof(t_minihell *minihell)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	free_str_arr(minihell->env);
	exit(EXIT_SUCCESS);
}

/*	minishell()
*	The main loop of minishell
*	Print a prompt, read user input and send that input to parsing
*/
void	minishell(t_minihell *minihell)
{
	char			*command_line;
	bool			ret;
	struct termios	t;

	using_history();
	ret = true;
	while (1)
	{
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		command_line = readline(BLUE_BOLD "minishell$ " RESET_COLOR);
		if (command_line == NULL)
			handle_eof(minihell);
		signal(SIGQUIT, handle_cmd);
		signal(SIGINT, handle_cmd);
		if (command_line && *command_line)
			add_history(command_line);
		ret = lexing(minihell, command_line);
		if (ret)
		{
			ret = parse(minihell);
			if (ret)
				execute(minihell);
			cleanup(minihell);
		}
	}
	tcgetattr(0, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

static void	init_minihell(t_minihell *minihell)
{
	minihell->tokens = NULL;
	minihell->env = NULL;
	minihell->pipe_fds = NULL;
	minihell->pids = NULL;
	minihell->nb_cmds = 0;
	minihell->heredocs = NULL;
	minihell->heredoc_nb = 0;
}

t_global	g_global;

int	main(int ac, char **av, char **envp)
{
	t_minihell	minihell;

	if (ac > 1)
	{
		ft_printf(2, "bash: %s: No such file or directory\n", av[1]);
		g_global.error_code = 127;
	}
	else
	{
		init_minihell(&minihell);
		init_env(&minihell, envp);
		minishell(&minihell);
		rl_clear_history();
	}
	return (0);
}
