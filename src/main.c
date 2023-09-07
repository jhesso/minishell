/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/07 15:12:44 by jhesso           ###   ########.fr       */
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
	char		*command_line;
	bool		ret;

	using_history();
	ret = true;
	while (1)
	{
		signals_interactive();
		command_line = readline(BLUE_BOLD "minishell$ " RESET_COLOR);
		if (command_line == NULL)
			handle_eof(minihell);
		signals_noninteractive();
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

	(void)ac;
	(void)av;
	init_minihell(&minihell);
	init_env(&minihell, envp);
	minishell(&minihell);
	rl_clear_history();
	return (0);
}
