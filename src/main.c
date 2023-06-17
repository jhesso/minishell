/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:15:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/17 12:58:15 by dgerguri         ###   ########.fr       */
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

	while (1)
	{
		command_line = readline(BLUE_BOLD "minishell >" RESET_COLOR);
		if (!ft_strncmp(command_line, "exit", 4))
			exit(EXIT_SUCCESS);
		ft_putendl_fd(command_line, STDOUT_FILENO);
		free (command_line);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	ft_printf("test");
	// init structs
	minishell();
	//exit shell
	return (0);
}
