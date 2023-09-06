/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:13:35 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 20:48:40 by jhesso           ###   ########.fr       */
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
	struct s_tokens	*cmds;
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

extern t_global	g_global;

/******************************************************************************/
/*								   Functions								  */
/******************************************************************************/

/*----------------------------------Lexing------------------------------------*/

/* lexing.c */
bool			lexing(t_minihell *minihell, char *command_line);

/* lexing_utils.c */
int				quotes(char const *s, int i);
bool			char_checker(char *command_line, int i, int flag);

/* tokenization.c */
int				get_amount_of_words(char const *s, char c);
int				get_word_len(char const *s, char c, int start);


/* syntax_checking.c */
bool			syntax_checker(char **tokens);

/*----------------------------------Parsing-----------------------------------*/

/* parsing.c */
bool			parse(t_minihell *minihell);
char    		*parse_str(int c, t_minihell *mini);

/* list.c */
bool			create_cmds(t_minihell *minihell);

/* expanding.c */
char			*expand_variables(char *str, char **envp);

/* expanding_utils.c */
char			*expand(char *str, char **envp, int start, int end);
char			*insert_value(char *str, char *value, int start, int new_start);
int				get_end_index(char *str, int i, int type);

/* removing_quotes.c */
char			*remove_quotes(char *str, int i, int j);

/*---------------------------------Execution----------------------------------*/

/* execute.c */
void			execute(t_minihell *mini);

/* execute_utils.c */
void			redirect_io(t_tokens *cmd, int **pipe_fds, int nb_cmd);
void			solo_builtin(t_minihell *mini, int i);

/* prepare_execution.c */
void			prepare_execution(t_minihell *minihell);

/* path.c */
void			append_command_path(t_minihell *minihell, t_tokens *cmds);

/* argv.c */
void			create_argv(t_minihell *minihell, t_tokens *tmp, int i, int options);

/* file.c */
void			open_files(t_minihell *minihell, int cmd, bool flag, bool error_flag);

/* heredoc.c */
int				heredoc(char *delim, char *name);
void			get_heredoc_name(t_minihell *mini, int cmd);

/* pipe */
// void			open_pipes(t_tokens *cmds);

/*---------------------------------Builtins-----------------------------------*/

/* builtin.c */
void			execute_builtin(t_minihell *minihell, int builtin);

/* exit.c */
void			exit_builtin(t_minihell *minihell);

/* echo.c */
void			echo_builtin(t_minihell *minihell, int j, int flag, int i);

/* pwd.c */
void			pwd_builtin(t_minihell *minihell);

/* env.c */
void			env_builtin(t_minihell *minihell);
void  			init_env(t_minihell *minihell, char **envp);

/* unset.c */
void			unset_builtin(t_minihell *mini);

/* export.c */
void			export_builtin(t_minihell *mini, int i, int argv_size);

/* cd.c */
void			cd_builtin(t_minihell *mini);

/* builtin_utils.c */
int				check_builtin(char *cmd);
int				invalid_variable(char *arg, int type);
int				already_exists(char **env, char *arg);
void			modify_variable(t_minihell *minihell, char *arg);
char			**export_variable(char **env, char *arg);

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
