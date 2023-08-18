/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:41:34 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/17 18:58:10 by jhesso           ###   ########.fr       */
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

	sizes.in = 0;
	sizes.out = 0;
	sizes.heredoc = 0;
	sizes.out_app = 0;
	sizes.options = -1;
	while (command_line[start] && command_line[start][0] != '|')
	{
		if (!ft_strncmp(command_line[start], "<\0", 2))
		{
			sizes.in++;
			start += 2;
		}
		else if (!ft_strncmp(command_line[start], "<<\0", 3))
		{
			sizes.heredoc++;
			start += 2;
		}
		else if (!ft_strncmp(command_line[start], ">\0", 2))
		{
			sizes.out++;
			start += 2;
		}
		else if (!ft_strncmp(command_line[start], ">>\0", 3))
		{
			sizes.out_app++;
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
		malloc_error();
	sizes = calculate_sizes(command_line, start);
	node->in = malloc(sizeof(char *) * (sizes.in + 1));
	node->out = malloc(sizeof(char *) * (sizes.out + 1));
	node->out_app = malloc(sizeof(char *) * (sizes.out_app + 1));
	node->heredoc = malloc(sizeof(char *) * (sizes.heredoc + 1));
	if (sizes.options > -1)
		node->opt = malloc(sizeof(char *) * (sizes.options + 1));
	else
		node->opt = malloc(sizeof(char *));
	if (node->in == NULL || node->out == NULL || node->heredoc == NULL
		|| (sizes.options > -1 && node->opt == NULL) || node->out_app == NULL)
		malloc_error();
	init_node(&node, sizes);
	return (node);
}

/*	create_node()
*	Allocate memory for a node of t_tokens
*	and save all the information for that node
*	Returns the index of the new pipe we found
*/
static int	create_node(char **c_line, int s, t_minihell *mini)
{
	t_tokens		*node;
	t_malloc_sizes	c;

	node = allocate_content(c_line, s);
	c = init_counter();
	node->command = NULL;
	while (c_line[s] && c_line[s][0] != '|')
	{
		if (!ft_strncmp(c_line[s], "<\0", 2))
			node->in[c.in++] = parse_str(c_line[++s], mini);
		else if (!ft_strncmp(c_line[s], "<<\0", 3))
			node->heredoc[c.heredoc++] = remove_quotes(c_line[++s], 0, 0);
		else if (!ft_strncmp(c_line[s], ">\0", 2))
			node->out[c.out++] = parse_str(c_line[++s], mini);
		else if (!ft_strncmp(c_line[s], ">>\0", 3))
			node->out_app[c.out_app++] = parse_str(c_line[++s], mini);
		else if (node->command != NULL)
			node->opt[c.options++] = parse_str(c_line[s], mini);
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
{
	int			i;

	minihell->lst_tokens = NULL;
	i = create_node(minihell->tokens, 0, minihell);
	if (minihell->tokens[i] && minihell->tokens[i][0] == '|')
	{
		// free (minihell->tokens[i]);
		i++;
	}
	while(minihell->tokens[i])
	{
		if (minihell->tokens[i][0] != '|')
			i = create_node(minihell->tokens, i, minihell);
		// else
		// 	free (minihell->tokens[i++]);
	}
	return (true);
}
