/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/08 05:35:53 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO:	create a "clean exit" function for when we need to exit for whatever reason like a malloc fail

/*	minishell()
*	The main loop of minishell
*	Print a prompt, read user input and send that input to parsing
*/
void	minishell(t_minihell *minihell)
{
	char		*command_line;

	using_history();
	while (1)
	{
		command_line = readline(BLUE_BOLD "minishell$ " RESET_COLOR);
		if (!ft_strncmp(command_line, "exit", 4)) //! this needs to be changed in the end, it is just temporary
			exit(EXIT_SUCCESS);
		if (command_line && *command_line) //* check that command_line is not just an empty line
			add_history(command_line); //* from what I understand, this adds the line to history but only for this session
		ft_putendl_fd(command_line, STDOUT_FILENO); //! this is just for testing
		lexing(minihell, command_line); //! if something can fail, change return type to bool
		if (parse(minihell) == false) //* idea is to return true or false based on if there is errors parsing
			ft_putendl_fd("parse error", STDERR_FILENO); //TODO: make this into something useful
		free (command_line); //? not sure if this is the right place to free it
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_minihell	minihell;

	init_env(&minihell, envp);
	minishell(&minihell);
	//exit shell
	//! seems that clear_history() is not allowed in the subject but checking the
	//! readline/history.h there is no function called rl_clear_history which is allowed in the subject
	clear_history(); // this needs to be moved to our exit routine once we have one
	return (0);
}
