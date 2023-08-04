/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:13:15 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/26 20:43:58 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	// ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("MALLOC ERROR", 2);
	exit(12); //! probably not the right way to exit, but it works for now
	//? error code 12!!!!!
}

t_malloc_sizes	init_counter(void)
{
	t_malloc_sizes	counter;

	counter.re_input = 0;
	counter.re_output = 0;
	counter.here_doc = 0;
	counter.options = 0;
	return (counter);
}

/*	lst_add_back()
*	add given node to the back of the given list
*/
void	lst_add_back(t_tokens **lst_tokens, t_tokens *node)
{
	t_tokens	*tmp;

	if (*lst_tokens == NULL)
	{
		*lst_tokens = node;
		return ;
	}
	tmp = *lst_tokens;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

/*	init_node()
*	Initialize default values for the contents of a node in our tokens list
*/
void	init_node(t_tokens **node)
{
	(*node)->input = NULL;
	(*node)->output = NULL;
	(*node)->heredoc_delim = NULL;
	(*node)->options = NULL;
	(*node)->command = NULL;
	(*node)->next = NULL;
}

/*	lst_print()
*	print given linked list's contents
*/
void	lst_print(t_tokens *lst_tokens)
{
	int	i;

	i = 0;
	while (lst_tokens)
	{
		ft_printf("node %d:\n", i);
		ft_printf("command: %s\n", lst_tokens->command);
		ft_printf("options:\n");
		i = 0;
		while (lst_tokens->options[i])
		{
			ft_printf("%s\n", lst_tokens->options[i]);
			i++;
		}
		ft_printf("input:\n");
		i = 0;
		while (lst_tokens->input[i])
		{
			ft_printf("%s\n", lst_tokens->input[i]);
			i++;
		}
		ft_printf("output:\n");
		i = 0;
		while (lst_tokens->output[i])
		{
			ft_printf("%s\n", lst_tokens->output[i]);
			i++;
		}
		ft_printf("heredoc_delim:\n");
		i = 0;
		while (lst_tokens->heredoc_delim[i])
		{
			ft_printf("%s\n", lst_tokens->heredoc_delim[i]);
			i++;
		}
		ft_printf("\n");
		lst_tokens = lst_tokens->next;
		i++;
	}
}
