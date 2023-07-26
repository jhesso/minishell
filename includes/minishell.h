/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/26 15:13:20 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET_COLOR	"\033[0m"    //reset color! Might delete it in the end, or change the location!
# define BLUE_BOLD   	"\033[0;34m" //color! Might delete it in the end, or change the location!

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

typedef struct s_lexer // this doesnt have to be a struct it can also be a variable inside the funciton!
{
	char	**tokens;
	int		double_quote; //if we dont need later we can delete and create variables inside the function check_quotes!
	int		single_quote; //if we dont need later we can delete and create variables inside the function check_quotes!
}			t_lexer;

/*	s_tokens
*	our linked list containing the given command line
*	each 'node' of the list contains one command including all of it's
*	options and redirections
*/
typedef struct			s_tokens
{
	char				*command;
	char				**options; // options for the command
	char				**input; // input redirections (filenames)
	char				**output; // output redirections (filenames)
	char				**heredoc_delim; // heredoc delimiter word(s)
	struct s_tokens		*next;
}						t_tokens;

/*	s_malloc_sizes
*	used to calculate and allocate the amount of memory needed for our tokens
*/
typedef struct		s_malloc_sizes
{
	int	re_input;
	int	re_output;
	int	here_doc;
	int options;
}	t_malloc_sizes;

/******************************************************************************/
/*								Functions									  */
/******************************************************************************/

/* lexing */
// void	lexing(char *command_line, t_lexer *tokens);
t_tokens	*lexing(char *command_line, t_lexer *tokens);

/* split_cmd */
char	**split_to_tokens(char const *s, char c);

/* lexing_utils */
void	quote_checker(char *command_line, t_lexer *tokens);

/* syntax check */
void	syntax_checker(char **tokens);

#endif
