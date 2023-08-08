/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/08 12:32:44 by jhesso           ###   ########.fr       */
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

typedef struct s_tokens	t_tokens;

/*	s_minihell
*	the 'main' struct of the project
*/
typedef struct s_minihell
{
	char			**tokens;
	char			**env;
	int				double_quote; //? if we dont need later we can delete and create variables inside the function check_quotes!
	int				single_quote; //? if we dont need later we can delete and create variables inside the function check_quotes!
	struct s_tokens	*lst_tokens; //* ptr to our linked list containing the given command line
}					t_minihell;

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
/*								   Functions								  */
/******************************************************************************/


/*----------------------------------Lexing------------------------------------*/

/* lexing.c */
void			lexing(t_minihell *command, char *command_line);

/* split_cmd.c */
char			**split_to_tokens(char const *s, char c);

/* lexing_utils.c */
void			quote_checker(char *command_line, t_minihell *command);

/* syntax_checker.c */
void			syntax_checker(char **tokens);

/*----------------------------------Parsing-----------------------------------*/

/* parsing.c */
bool			parse(t_minihell *minihell);

/* list.c */
t_tokens		*create_lst_tokens(char **command_line);

/* lst_utils.c */
void			malloc_error(void);
t_malloc_sizes	init_counter(void);
void			init_node(t_tokens **node);
void			lst_print(t_tokens *lst_tokens);
void			lst_add_back(t_tokens **lst_tokens, t_tokens *node);

/*----------------------------------Builtins-----------------------------------*/

void	init_env(t_minihell *command, char **envp);

#endif
