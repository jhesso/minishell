/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/23 17:40:27 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET_COLOR	"\033[0m"    //reset color! Might delete it in the end, or change the location!
# define BLUE_BOLD   	"\033[0;34m" //color! Might delete it in the end, or change the location!
# define PROMPT			"BLUE_BOLD minishell$ RESET_COLOR" // I dont think this works as I wanted it to

/******************************************************************************/
/*								Includes  									  */
/******************************************************************************/

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/includes/libft.h"

/******************************************************************************/
/*								Structs 									  */
/******************************************************************************/

typedef struct s_lexer
{
	char	**tokens;
	int		double_quote; //if we dont need later we can delete and create variables inside the function check_quotes!
	int		single_quote; //if we dont need later we can delete and create variables inside the function check_quotes!
}			t_lexer;

typedef struct			s_commands
{
	char				*command;
	char				**options; // options for the command
	char				**input; // input redirections (filenames)
	char				**output; // output redirections (filenames)
	char				*heredoc_delim; // heredoc delimiter word
	struct s_commands	*next;
}						t_commands;

/******************************************************************************/
/*								Functions									  */
/******************************************************************************/

/* lexing */
void	lexing(char *command_line, t_lexer *tokens);

/* lexing_utils */
void	check_quotes(char *command_line, t_lexer *tokens);

#endif
