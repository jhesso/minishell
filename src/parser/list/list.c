/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:41:34 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/07 15:52:13 by jhesso           ###   ########.fr       */
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
		if (!ft_strncmp(command_line[start], "<\0", 2) || \
			!ft_strncmp(command_line[start], "<<\0", 3) || \
			!ft_strncmp(command_line[start], ">\0", 2) || \
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
static t_cmds	*allocate_content(char **command_line, int start)
{
	int		size_opt;
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
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

/*	lst_add_back()
*	add given node to the back of the given list
*/
static void	lst_add_back(t_cmds **cmds, t_cmds *node)
{
	t_cmds	*tmp;

	if (*cmds == NULL)
	{
		*cmds = node;
		return ;
	}
	tmp = *cmds;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

/*	create_node()
*	Allocate memory for a node of t_cmds
*	and save all the information for that node
*	Returns the index of the new pipe we found
*/
static int	create_node(char **c_line, int s, t_minihell *mini, int c)
{
	t_cmds	*node;
	char	*ret;

	node = allocate_content(c_line, s);
	node->command = NULL;
	while (c_line[s] && c_line[s][0] != '|')
	{
		if (!ft_strncmp(c_line[s], "<\0", 2) || \
			!ft_strncmp(c_line[s], "<<\0", 3) || \
			!ft_strncmp(c_line[s], ">\0", 2) || \
			!ft_strncmp(c_line[s], ">>\0", 3))
			parse_str(++s, mini);
		else
		{
			ret = remove_quotes(parse_str(s, mini), 0, 0, 0);
			if (node->command != NULL && ret)
				node->opt[c++] = ret;
			else if (ret)
				node->command = ret;
		}
		s++;
	}
	lst_add_back(&mini->cmds, node);
	return (s);
}

/*
*	loop through the command_line char**
*	each time we hit a '|', create a new node containing everything after that pipe
*	until we reach a new pipe (or the end of command_line)
*	return the finished lst_token list
*/
bool	create_cmds(t_minihell *minihell)
{
	int			i;

	minihell->cmds = NULL;
	i = create_node(minihell->tokens, 0, minihell, 0);
	if (minihell->tokens[i] && minihell->tokens[i][0] == '|')
		i++;
	while (minihell->tokens[i])
	{
		if (minihell->tokens[i][0] != '|')
			i = create_node(minihell->tokens, i, minihell, 0);
		else
			i++;
	}
	return (true);
}
