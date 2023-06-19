/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/19 17:44:32 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	minishell()
*	The main loop of minishell
*	Print a prompt, read user input and send that input to parsing
*/
void	minishell(void)
{
	char	*command_line;
	t_lexer	tokens; //dgerguri: will save the **arr of tokens.
	//I initialized here, to make it easier to be used from parsing and further steps!

	while (1)
	{
		command_line = readline(PROMPT);
		if (!ft_strncmp(command_line, "exit", 4))
			exit(EXIT_SUCCESS);
		if (command_line && *command_line) // check that command_line is not just an empty line
			add_history(command_line); // from what I understand, this adds the line to history but only for this session
		ft_putendl_fd(command_line, STDOUT_FILENO);
		lexing(command_line, &tokens);
		free (command_line);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	// init structs
	minishell();
	//exit shell
	rl_clear_history(); // this needs to be moved to our exit routine once we have one
	return (0);
}
