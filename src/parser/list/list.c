/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:41:34 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/26 20:59:53 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	calculate_sizes()
*	Calculate the amount of strings each variable needs to hold in a node of
*	our tokens list
*	Returns a struct containing the calculated values
*/
static t_malloc_sizes	calculate_sizes(char **command_line, int start)
{
	t_malloc_sizes	sizes;

	sizes.re_input = 0;
	sizes.re_output = 0;
	sizes.here_doc = 0;
	sizes.options = -1;
	while (command_line[start] && command_line[start][0] != '|')
	{
		if (!ft_strncmp(command_line[start], "<\0", 2))
		{
			sizes.re_input++;
			start++;
		}
		else if (!ft_strncmp(command_line[start], "<<", 2))
		{
			sizes.here_doc++;
			start++;
		}
		else if (!ft_strncmp(command_line[start], ">", 1))
		{
			sizes.re_output++;
			start++;
		}
		else
			sizes.options++;
		start++;
	}
	return (sizes);
}

/*	allocate_content()
*	Allocate memory for the contents of a node in our tokens list
*/
static t_tokens	*allocate_content(char **command_line, int start, t_tokens *node)
{
	t_malloc_sizes	sizes;

	sizes = calculate_sizes(command_line, start);
	node->input = malloc(sizeof(char *) * sizes.re_input + 1);
	node->output = malloc(sizeof(char *) * sizes.re_output + 1);
	node->heredoc_delim = malloc(sizeof(char *) * sizes.here_doc + 1);
	if (sizes.options > -1)
		node->options = malloc(sizeof(char *) * sizes.options + 1);
	if (node->input == NULL || node->output == NULL || node->heredoc_delim == NULL
		|| (sizes.options > -1 && node->options == NULL))
		malloc_error(); //! add malloc protection
	init_node(&node);
	return (node);
}

/*	create_node()
*	Allocate memory for a node of t_tokens
*	and save all the information for that node
*	Returns the index of the new pipe we found
*/
static int	create_node(char **command_line, int start, t_tokens **lst_tokens)
{ // TODO: check the calculated amounts of strings and that we allocate enough memory. if thats the reason for sanitizer errror
	t_tokens		*node;
	t_malloc_sizes	counter; //* repurposing the struct to use as indexes instead of sizes
	// Allocate memory for a node and its contents
	node = malloc(sizeof(t_tokens)); //! add malloc protection
	node = allocate_content(command_line, start, node);
	// save the content correctly to the node
	counter = init_counter();
	ft_putstr_fd("we get this far\n", STDOUT_FILENO); //! this is just for testing
	while (command_line[start] && command_line[start][0] != '|')
	{
		if (!ft_strncmp(command_line[start], "<\0", 2))
			node->input[counter.re_input++] = ft_strdup(command_line[++start]);
		else if (!ft_strncmp(command_line[start], "<<", 2))
			node->heredoc_delim[counter.here_doc++] = ft_strdup(command_line[++start]);
		else if (!ft_strncmp(command_line[start], ">\0", 2))
			node->output[counter.re_output++] = ft_strdup(command_line[++start]);
		else if (node->command != NULL)
			node->options[counter.options++] = ft_strdup(command_line[start]);
		else
			node->command = ft_strdup(command_line[start]);
		start++;
	}
	lst_add_back(lst_tokens, node);
	return (start);
}

/*
*	loop through the command_line char**
*	each time we hit a '|', create a new node containing everything after that pipe
*	until we reach a new pipe (or the end of command_line)
*	return the finished lst_token list
*/
t_tokens	*create_lst_tokens(char **command_line)
{
	t_tokens	*lst_tokens;
	int			i;

	i = 0;
	i = create_node(command_line, i, &lst_tokens);
	while(command_line[i])
	{
		if (command_line[i][0] == '|')
			i = create_node(command_line, i, &lst_tokens);
		else
			i++; //? the whole if else can be replaced with i = create_node(command_line, i, &lst_tokens);?
	}
	return (lst_tokens);
}
