/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/30 03:20:47 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_eof(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

/*	minishell()
*	The main loop of minishell
*	Print a prompt, read user input and send that input to parsing
*/
void	minishell(t_minihell *minihell)
{
	char		*command_line;
	bool		ret; // return value of our functions, if set to false, error happened

	using_history();
	ret = true;
	while (1)
	{
		signals_interactive();
		command_line = readline(BLUE_BOLD "minishell$ " RESET_COLOR);
		if (command_line == NULL)
			handle_eof();
		signals_noninteractive();
		if (command_line && *command_line) //* check that command_line is not just an empty line
			add_history(command_line); //* from what I understand, this adds the line to history but only for this session
		// ft_putendl_fd(command_line, STDOUT_FILENO); //! this is just for testing
		ret = lexing(minihell, command_line);
		if (ret)
		{
			ret = parse(minihell);
			if (ret)
				execute(minihell);
			cleanup(minihell);
		}
		// system("leaks minishell"); //! this is just for testing
	}
}
int	error_code = 0;

static void	init_minihell(t_minihell *minihell)
{
	minihell->tokens = NULL;
	minihell->env = NULL;
	minihell->double_quote = 0;
	minihell->single_quote = 0;
	minihell->pipe_fds = NULL;
	minihell->pids = NULL;
	minihell->nb_cmds = 0;
	// minihell->lst_tokens = NULL;
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_minihell	minihell;

	init_minihell(&minihell);
	init_env(&minihell, envp);
	minishell(&minihell);
	//exit shell
	//! seems that clear_history() is not allowed in the subject but checking the
	//! readline/history.h there is no function called rl_clear_history which is allowed in the subject
	rl_clear_history(); // this needs to be moved to our exit routine once we have one
	return (0);
}
