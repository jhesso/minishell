/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/23 05:05:59 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET_COLOR	"\033[0m"
# define BLUE_BOLD   	"\033[0;34m"

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
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/includes/libft.h"

/******************************************************************************/
/*								Structs 									  */
/******************************************************************************/

extern int				error_code;

typedef struct s_tokens	t_tokens;

/*	s_minihell
*	the 'main' struct of the project
*	double_quote and single_quote can maybe be simply moved
*	to the function that needs them instead of being in the struct
*/
typedef struct s_minihell
{
	char			**tokens;
	char			**env;
	int				double_quote;
	int				single_quote;
	int				pipe_fds[2];
	int				old_fds[2];
	pid_t			*pids;
	int				nb_cmds;
	struct s_tokens	*lst_tokens;
}					t_minihell;

/*	s_tokens
*	our linked list containing the given command line
*	each 'node' of the list contains one command including all of it's
*	options and redirections
*	opt being the options for the command
*	in, out, out_app and heredoc being the fds/delim word for redirections
*	argv being the command and it's options, this is what is given to execve
*	fd_in and fd_out being the file descriptors for redirections
*	note that fd_in, fd_out and argv are allocated later on in the program!
*/
typedef struct			s_tokens
{
	char				*command;
	char				**opt;
	char				**in;
	char				**out;
	char				**out_app;
	char				**heredoc;
	char				**argv;
	int					fd_in;
	int					fd_out;
	struct s_tokens		*next;
}						t_tokens;

/*	s_malloc_sizes
*	used to calculate and allocate the amount of memory needed for our tokens
*/
typedef struct		s_malloc_sizes
{
	int	in;
	int	out;
	int out_app;
	int	heredoc;
	int options;
}	t_malloc_sizes;

/******************************************************************************/
/*								   Functions								  */
/******************************************************************************/

/*----------------------------------Lexing------------------------------------*/

/* lexing.c */
bool			lexing(t_minihell *command, char *command_line);

/* tokenization.c */
int				get_amount_of_words(char const *s, char c);
int				get_word_len(char const *s, char c, int start);

/* lexing_utils.c */
bool			char_checker(char *command_line, t_minihell *command, int i);
int				quotes(char const *s, int i);

/* syntax_checking.c */
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

/* removing_quotes.c */
char			*remove_quotes(char *str, int i, int j);

/*---------------------------------Execution----------------------------------*/

/* execute.c */
bool			execute(t_minihell *minihell);

/* prepare_execution.c */
void			prepare_execution(t_minihell *minihell);

/* path.c */
void			append_command_path(t_minihell *minihell);

/* argv.c */
void			create_argv(t_minihell *minihell);

/* file.c */
void			open_files(t_minihell *minihell);

/* pipe */
void			open_pipes(t_tokens *lst_tokens);

/*---------------------------------Builtins-----------------------------------*/

/* builtin.c */
void			execute_builtin(t_minihell *minihell, int builtin);

void  			init_env(t_minihell *minihell, char **envp);

void			env_builtin(t_minihell *minihell);
void			pwd_builtin(void);
void			echo_builtin(t_tokens *cmd);
void			export_builtin(t_minihell *minihell);

/* builtin_utils.c */
int				check_builtin(char *cmd);

/*----------------------------------Signals-----------------------------------*/

/* signals.c */
void			signals_interactive(void);
void			signals_noninteractive(void);

/*----------------------------------Utils-------------------------------------*/

/* cleanup.c */
void			cleanup(t_minihell *minihell);
void			*free_str_arr(char **s);

/* utils.c */
int				count_strings(char **array);

#endif
