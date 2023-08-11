/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/11 16:43:27 by dgerguri         ###   ########.fr       */
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
	char				**opt; // options for the command
	char				**in; // input redirections (filenames)
	char				**out; // output redirections (filenames)
	char				**out_app; // output redirections (filenames, append mode)
	char				**heredoc; // heredoc delimiter word(s)
	struct s_tokens		*next;
}						t_tokens;

/*	s_malloc_sizes
*	used to calculate and allocate the amount of memory needed for our tokens
*/
typedef struct		s_malloc_sizes
{
	int	re_in;
	int	re_out;
	int re_out_app;
	int	here_doc;
	int options;
}	t_malloc_sizes;

/******************************************************************************/
/*								   Functions								  */
/******************************************************************************/

/*----------------------------------Lexing------------------------------------*/

/* lexing.c */
bool	lexing(t_minihell *command, char *command_line);

/* split_cmd.c */
char	**tokenize_cmd(char const *s, char c);

/* lexing_utils.c */
bool			character_checker(char *command_line, t_minihell *command, int i);
int				quotes(char const *s, int i);
char			**free_allocated_strings(char **ret, int row); //We should move this somewhere else and this should be universal!

/* syntax_checker.c */
bool			syntax_checker(char **tokens);

/*----------------------------------Parsing-----------------------------------*/

/* parsing.c */
bool			parse(t_minihell *minihell);

/* list.c */
bool			create_lst_tokens(t_minihell *minihell);

/* lst_utils.c */
void			malloc_error(void);
t_malloc_sizes	init_counter(void);
void			init_node(t_tokens **node, t_malloc_sizes sizes);
void			lst_print(t_tokens *lst_tokens);
void			lst_add_back(t_tokens **lst_tokens, t_tokens *node);
void			print_sizes(t_malloc_sizes sizes);

char			*parse_str(char *str, t_minihell *minihell);
char			*remove_quotes(char *str, int i, int j);

/*----------------------------------Builtins-----------------------------------*/

void  			init_env(t_minihell *minihell, char **envp);

#endif
