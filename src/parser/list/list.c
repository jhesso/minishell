/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:41:34 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/09 19:38:49 by jhesso           ###   ########.fr       */
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

	sizes.re_in = 0;
	sizes.re_out = 0;
	sizes.here_doc = 0;
	sizes.re_out_app = 0;
	sizes.options = -1; //* start options at -1 since the first non special character is the command
	while (command_line[start] && command_line[start][0] != '|')
	{
		if (!ft_strncmp(command_line[start], "<\0", 2))
		{
			sizes.re_in++;
			start += 2;
		}
		else if (!ft_strncmp(command_line[start], "<<\0", 3))
		{
			sizes.here_doc++;
			start += 2;
		}
		else if (!ft_strncmp(command_line[start], ">\0", 2))
		{
			sizes.re_out++;
			start += 2;
		}
		else if (!ft_strncmp(command_line[start], ">>\0", 3))
		{
			sizes.re_out_app++;
			start += 2;
		}
		else
		{
			sizes.options++;
			start++;
		}
	}
	return (sizes);
}

/*	allocate_content()
*	Allocate memory for the contents of a node in our tokens list
*/
static t_tokens	*allocate_content(char **command_line, int start)
{
	t_malloc_sizes	sizes;
	t_tokens		*node;

	node = malloc(sizeof(t_tokens));
	if (node == NULL)
		malloc_error(); //! add malloc protection
	sizes = calculate_sizes(command_line, start);
	print_sizes(sizes);
	node->in = malloc(sizeof(char *) * (sizes.re_in + 1));
	node->out = malloc(sizeof(char *) * (sizes.re_out + 1));
	node->out_app = malloc(sizeof(char *) * (sizes.re_out_app + 1));
	node->heredoc = malloc(sizeof(char *) * (sizes.here_doc + 1));
	if (sizes.options > -1)
		node->opt = malloc(sizeof(char *) * (sizes.options + 1));
	if (node->in == NULL || node->out == NULL || node->heredoc == NULL
		|| (sizes.options > -1 && node->opt == NULL) || node->out_app == NULL)
		malloc_error(); //! add malloc protection
	init_node(&node, sizes);
	return (node);
}

/*	create_node()
*	Allocate memory for a node of t_tokens
*	and save all the information for that node
*	Returns the index of the new pipe we found
*/
static int	create_node(char **c_line, int s, t_minihell *mini)
{ // TODO: check the calculated amounts of strings and that we allocate enough memory. if thats the reason for sanitizer errror
	t_tokens		*node;
	t_malloc_sizes	counter; //* repurposing the struct to use as indexes instead of sizes

	node = allocate_content(c_line, s);
	counter = init_counter();
	node->command = NULL;
	while (c_line[s] && c_line[s][0] != '|')
	{
		ft_printf("c_line[%d] = %s\n", s, c_line[s]);
		if (!ft_strncmp(c_line[s], "<\0", 2))
			node->in[counter.re_in++] = parse_str(c_line[++s], mini); //TODO: open the file immediately and save the fd instead of the filename
		else if (!ft_strncmp(c_line[s], "<<\0", 3))
			node->heredoc[counter.here_doc++] = parse_str(c_line[++s], mini); //TODO: open the file immediately and save the fd instead of the filename
		else if (!ft_strncmp(c_line[s], ">\0", 2))
			node->out[counter.re_out++] = parse_str(c_line[++s], mini); //TODO: open the file immediately and save the fd instead of the filename
		else if (!ft_strncmp(c_line[s], ">>\0", 3))
			node->out_app[counter.re_out_app++] = parse_str(c_line[++s], mini);//TODO: open the file immediately and save the fd instead of the filename
		else if (node->command != NULL)
			node->opt[counter.options++] = parse_str(c_line[s], mini);
		else
			node->command = parse_str(c_line[s], mini);
		s++;
	}
	lst_add_back(&mini->lst_tokens, node);
	return (s);
}

/*
*	loop through the command_line char**
*	each time we hit a '|', create a new node containing everything after that pipe
*	until we reach a new pipe (or the end of command_line)
*	return the finished lst_token list
*/
bool	create_lst_tokens(t_minihell *minihell)
{ //! no malloc protection yet
	int			i;

	i = create_node(minihell->tokens, 0, minihell);
	ft_printf("i = %d\n", i);
	ft_printf("starting while loop inside create_lst_tokens\n");
	while(minihell->tokens[i])
	{
		if (minihell->tokens[i][0] == '|')
			i = create_node(minihell->tokens, i, minihell);
		else
			i++; //? the whole if else can be replaced with i = create_node(minihell->tokens, i, &lst_tokens);?
	}
	return (true);
}
