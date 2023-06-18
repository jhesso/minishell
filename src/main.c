/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/18 15:32:22 by dgerguri         ###   ########.fr       */
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
	t_lexer	tokens; //dgerguri: this will be the linked list with all the tokens.
	//I initialized here, to make it easier to bbe used from parsing and further steps!

	while (1)
	{
		command_line = readline("minishell >");
		if (!ft_strncmp(command_line, "exit", 4))
			exit(EXIT_SUCCESS);
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
	return (0);
}
