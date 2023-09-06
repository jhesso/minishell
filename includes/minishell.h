/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 18:57:28 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET_COLOR "\001\e[0;m\002"
# define BLUE_BOLD "\001\e[0;34m\002"

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
	int				**pipe_fds;
	pid_t			*pids;
	int				nb_cmds;
	char			**heredocs;
	int				heredoc_nb;
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
	char				**argv;
	int					fd_in;
	int					fd_out;
	struct s_tokens		*next;
}						t_tokens;

typedef struct	s_global
{
	int			heredoc_tmp;
	int			error_code;
}				t_global;

/******************************************************************************/
/*								   GLOBAL									  */
/******************************************************************************/

extern t_global	global;

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
bool			char_checker(char *command_line, int i);
int				quotes(char const *s, int i);

/* syntax_checking.c */
bool			syntax_checker(char **tokens);

/*----------------------------------Parsing-----------------------------------*/

/* parsing.c */
bool			parse(t_minihell *minihell);
char    		*parse_str(int c, t_minihell *minihell);

/* list.c */
bool			create_lst_tokens(t_minihell *minihell);

/* lst_utils.c */
void			lst_print(t_tokens *lst_tokens);
void			lst_add_back(t_tokens **lst_tokens, t_tokens *node);

/* expanding.c */
char			*expand_variables(char *str, char **envp);

/* removing_quotes.c */
char			*remove_quotes(char *str, int i, int j);

/*---------------------------------Execution----------------------------------*/

/* execute.c */
void			execute(t_minihell *mini);

/* prepare_execution.c */
void			prepare_execution(t_minihell *minihell);

/* path.c */
void			append_command_path(t_minihell *minihell, t_tokens *lst_tokens);

/* argv.c */
void			create_argv(t_minihell *minihell);

/* file.c */
void			open_files(t_minihell *minihell, int cmd);

/* heredoc.c */
int				heredoc(char *delim, char *name);
void			get_heredoc_name(t_minihell *mini, int cmd);

/* pipe */
// void			open_pipes(t_tokens *lst_tokens);

/*---------------------------------Builtins-----------------------------------*/

/* builtin.c */
void			execute_builtin(t_minihell *minihell, int builtin);

void  			init_env(t_minihell *minihell, char **envp);

void			exit_builtin(t_minihell *minihell);
void			echo_builtin(t_minihell *minihell, int j, int flag, int i);
void			pwd_builtin(t_minihell *minihell);
void			env_builtin(t_minihell *minihell);
void			unset_builtin(t_minihell *minihell);
void			export_builtin(t_minihell *minihell);
void			cd_builtin(t_minihell *minihell);

int				already_exists(char **env, char *arg);
void			modify_variable(t_minihell *minihell, char *arg);
char			**export_variable(char **env, char *arg);

/* builtin_utils.c */
int				check_builtin(char *cmd);
int				invalid_variable(char *arg, int type);

/*----------------------------------Signals-----------------------------------*/

/* signals.c */
void			signals_interactive(void);
void			signals_noninteractive(void);

/*----------------------------------Utils-------------------------------------*/

/* cleanup.c */
void			cleanup(t_minihell *minihell);
void			*free_str_arr(char **s);
void			close_pipes(t_minihell *mini);

/* utils.c */
void			*free_str_arr(char **s);
int				count_strings(char **array);

/* error.c */
void			malloc_error(void);
void			dup_error(void);



char			*get_value(char *path, int len, char **envp);

#endif
