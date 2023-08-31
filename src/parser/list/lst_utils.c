/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:13:15 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/31 18:01:03 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	// ft_putstr_fd(strerror(errno), 2);
	ft_printf(2, "Error: Malloc Error!");
	exit(12); //! probably not the right way to exit, but it works for now
	//? error code 12!!!!!
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

/*	lst_print()
*	print given linked list's contents
*/
void	lst_print(t_tokens *lst_tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\nlst_print:\n");
	while (lst_tokens)
	{
		printf("node %d:\n", j);
		printf("	command: %s\n", lst_tokens->command);
		printf("	options:\n");
		i = 0;
		while (lst_tokens->opt[i])
		{
			printf("		opt[%d]: %s\n", i, lst_tokens->opt[i]);
			i++;
		}
		lst_tokens = lst_tokens->next;
		j++;
	}
}
