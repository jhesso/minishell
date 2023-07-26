/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/06 17:53:511 by dgerguri         ###   ########.fr       */
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
	// while (tokens[start] && !ft_strrchr("|\0", tokens[start][0])) //delete this
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
	// printf("%d, %d, %d, %d\n", sizes->re_input, sizes->re_output, sizes->here_doc, sizes->options);
	return (start);
}

static void	init_values(t_tokens **lst_tokens)
{
	(*lst_tokens)->input = NULL;
	(*lst_tokens)->output = NULL;
	(*lst_tokens)->heredoc_delim = NULL;
	(*lst_tokens)->options = NULL;
	(*lst_tokens)->command = NULL;
	(*lst_tokens)->next = NULL;
}

int	mem_allocation(t_tokens **lst_tokens, char **tokens, int start)
{
	t_malloc_sizes sizes;

	start = count_strings(tokens, start, &sizes);
	// printf("%d, %d, %d, %d\n", sizes.re_input, sizes.re_output, sizes.here_doc, sizes.options);
	(*lst_tokens)->input = malloc(sizeof(char *) * (sizes.re_input) + 1);
	if ((*lst_tokens)->input == NULL)
		malloc_error();
	(*lst_tokens)->output = malloc(sizeof(char *) * (sizes.re_output) + 1);
	if ((*lst_tokens)->output == NULL)
		malloc_error();
	(*lst_tokens)->heredoc_delim = malloc(sizeof(char *) * (sizes.here_doc) + 1);
	if ((*lst_tokens)->heredoc_delim == NULL)
		malloc_error();
	if (sizes.options >= 0)
	{
		(*lst_tokens)->options = malloc(sizeof(char *) * (sizes.options) + 1);
		if ((*lst_tokens)->options == NULL)
			malloc_error();
	}
	init_values(lst_tokens);
	return (start);
}

t_tokens	*create_lst_tokens(char **command_line, int i, t_tokens **lst_tokens)
{
	// t_tokens	*lst_tokens; //change the name
	// might need to dereference this with *
	lst_tokens = malloc(sizeof * lst_tokens); // allocate the node
	if (lst_tokens == NULL)
		return (NULL);
	if (command_line[i]) // check that we didnt hit null I think we dont need this check at all do we?? not sure
	{
		if (command_line[i] && command_line[i][0] != '|') // hit pipe or end of command_line
		{
			i = mem_allocation(lst_tokens, command_line, i); // i becomes location of pipe
			// we write a function here where we create the strings for all the variables in the struct!
		}
		// i++; // do we need this now that the while loop is gone? maybe :D idk no we can pot i + 1 inside
		if (command_line[i][0] == '|') //check this does it make sense
			(*lst_tokens)->next = create_lst_tokens(command_line, i + 1, lst_tokens);
		else
			(*lst_tokens)->next = NULL;
	}
	return (lst_tokens);
}

t_tokens	*lexing(char *command_line, t_lexer *tokens)
{
	t_tokens	*lst_tokens;

	quote_checker(command_line, tokens);
	tokens->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(tokens->tokens);
	lst_tokens = create_lst_tokens(tokens->tokens, 0, &lst_tokens);   //jhesso I changes some names, but still might not be good!!!

}
