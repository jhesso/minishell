/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:13:15 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/09 18:30:17 by jhesso           ###   ########.fr       */
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

	counter.re_in = 0;
	counter.re_out = 0;
	counter.re_out_app = 0;
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
*	Initialize the node by setting the last element of each array as NULL
*	effectively null terminating the arrays so we dont buffer overflow later :>
*/
void	init_node(t_tokens **node, t_malloc_sizes sizes)
{
	(*node)->in[sizes.re_in] = NULL;
	(*node)->out[sizes.re_out] = NULL;
	(*node)->out_app[sizes.re_out_app] = NULL;
	(*node)->heredoc[sizes.here_doc] = NULL;
	if (sizes.options > -1)
		(*node)->opt[sizes.options] = NULL;
	else
		(*node)->opt[0] = NULL;
	(*node)->command = NULL;
	(*node)->next = NULL;
}

void	print_sizes(t_malloc_sizes sizes)
{
	ft_printf("re_in: %d\n", sizes.re_in);
	ft_printf("re_out: %d\n", sizes.re_out);
	ft_printf("re_out_app: %d\n", sizes.re_out_app);
	ft_printf("here_doc: %d\n", sizes.here_doc);
	ft_printf("options: %d\n", sizes.options);
}

/*	lst_print()
*	print given linked list's contents
*/
void	lst_print(t_tokens *lst_tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("lst_print:\n");
	while (lst_tokens)
	{
		ft_printf("node %d:\n", j);
		ft_printf("	command: %s\n", lst_tokens->command);
		ft_printf("	options:\n");
		i = 0;
		while (lst_tokens->opt[i])
		{
			ft_printf("		opt[%d]: %s\n", i, lst_tokens->opt[i]);
			i++;
		}
		ft_printf("	input:\n");
		i = 0;
		while (lst_tokens->in[i])
		{
			ft_printf("		input[%d]: %s\n", i, lst_tokens->in[i]);
			i++;
		}
		ft_printf("	output:\n");
		i = 0;
		while (lst_tokens->out[i])
		{
			ft_printf("		output[%d]: %s\n", i, lst_tokens->out[i]);
			i++;
		}
		ft_printf("	output_append:\n");
		i = 0;
		while (lst_tokens->out_app[i])
		{
			ft_printf("		output_append[%d]: %s\n", i, lst_tokens->out_app[i]);
			i++;
		}
		ft_printf("	heredoc:\n");
		i = 0;
		while (lst_tokens->heredoc[i])
		{
			ft_printf("		heredoc[%d]: %s\n", i, lst_tokens->heredoc[i]);
			i++;
		}
		lst_tokens = lst_tokens->next;
		j++;
	}
}
