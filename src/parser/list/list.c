/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:41:34 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/30 19:54:45 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	calculate_sizes()
*	Calculate the amount of strings each variable needs to hold in a node of
*	our tokens list
*	Returns a struct containing the calculated values
*/
static int	calculate_options(char **command_line, int start)
{
	int	size_opt;

	size_opt = -1;
	while (command_line[start] && command_line[start][0] != '|')
	{
		if (!ft_strncmp(command_line[start], "<\0", 2) ||
			!ft_strncmp(command_line[start], "<<\0", 3) ||
			!ft_strncmp(command_line[start], ">\0", 2) ||
			!ft_strncmp(command_line[start], ">>\0", 3))
			start += 2;
		else
		{
			size_opt++;
			start++;
		}
	}
	return (size_opt);
}

/*	allocate_content()
*	Allocate memory for the contents of a node in our tokens list
*/
static t_tokens	*allocate_content(char **command_line, int start)
{
	int			size_opt;
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (node == NULL)
		malloc_error();
	size_opt = calculate_options(command_line, start);
	if (size_opt > -1)
        node->opt = ft_calloc(sizeof(char *), (size_opt + 1));
    else
	{
		node->opt = malloc(sizeof(char *));
		node->opt[0] = NULL;
	}
	if (size_opt > -1 && !node->opt)
		malloc_error();
	node->command = NULL;
	node->next = NULL;
	return (node);
}

/*	create_node()
*	Allocate memory for a node of t_tokens
*	and save all the information for that node
*	Returns the index of the new pipe we found
*/
static int  create_node(char **c_line, int s, t_minihell *mini)
{
    t_tokens	*node;
	int			c;

    node = allocate_content(c_line, s);
	c = 0;
    node->command = NULL;
    while (c_line[s] && c_line[s][0] != '|')
    {
        if (!ft_strncmp(c_line[s], "<\0", 2) ||
			!ft_strncmp(c_line[s], "<<\0", 3) ||
			!ft_strncmp(c_line[s], ">\0", 2) ||
			!ft_strncmp(c_line[s], ">>\0", 3))
			parse_str(++s, mini);
        else if (node->command != NULL)
            node->opt[c++] = parse_str(s, mini);
		else
            node->command = parse_str(s, mini);
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
		else
			i++;
		// 	free (minihell->tokens[i++]);
	}
	return (true);
}
