/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/05 18:01:00 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error()
{

	// ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("MALLOC ERROR", 2);
	//error code 12!!!!!
}

int	count_strings(char **tokens, int start, t_malloc_sizes *sizes)
{
	sizes->re_input = 0;
	sizes->re_output = 0;
	sizes->here_doc = 0;
	sizes->options = -1;
	while (tokens[start] && tokens[start][0] != '|')
	{
		if (!ft_strncmp(tokens[start], "<\0", 2))
		{
			sizes->re_input++;
			start++;
		}
		else if (!ft_strncmp(tokens[start], "<<", 2))
		{
			sizes->here_doc++;
			start++;
		}
		else if (!ft_strncmp(tokens[start], ">", 1))
		{
			sizes->re_output++;
			start++;
		}
		else
			sizes->options++;
		start++;
	}
	printf("%d, %d, %d, %d\n", sizes->re_input, sizes->re_output, sizes->here_doc, sizes->options);
	return (start);
}

int	mem_allocation(t_commands *commands, char **tokens, int start)
{
	t_malloc_sizes sizes;

	count_strings(tokens, start, &sizes);
	commands->input = malloc(sizeof(char *) * (sizes.re_input) + 1);
	if (commands->input == NULL)
		malloc_error();
	commands->output = malloc(sizeof(char *) * (sizes.re_output) + 1);
	if (commands->output == NULL)
		malloc_error();
	commands->heredoc_delim = malloc(sizeof(char *) * (sizes.here_doc) + 1);
	if (commands->heredoc_delim == NULL)
		malloc_error();
	if (sizes.options >= 0)
	{
		commands->options = malloc(sizeof(char *) * (sizes.here_doc) + 1);
		if (commands->options == NULL)
			malloc_error();
	}
	return(start);
}

t_commands	*command_type(char **tokens)
{
	t_commands	*commands; //change the name
	int			start;

	commands = malloc(sizeof * commands);
	if (commands == NULL)
		return (NULL);
	start = 0;

	while (tokens[start])
	{
		if (tokens[start] && tokens[start][0] != '|')
		{
			start = mem_allocation(commands, tokens, start); //change the name!
		}
		start++;
		commands = commands->next;
	}
}

void	lexing(char *command_line, t_lexer *tokens)
{
	t_commands *cmd;

	quote_checker(command_line, tokens);
	tokens->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(tokens->tokens);
	cmd = command_type(tokens->tokens);   //jhesso I have no idea what to name it :(


	//This is to test the tokens!
	// int i = 0;
	// while (tokens->tokens[i] != NULL)
	// {
	// 	printf("%s\n", tokens->tokens[i]);
	// 	i++;
	// }
}
