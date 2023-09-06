/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:13:15 by jhesso            #+#    #+#             */
/*   Updated: 2023/09/06 19:20:03 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	lst_add_back()
*	add given node to the back of the given list
*/
void	lst_add_back(t_tokens **cmds, t_tokens *node)
{
	t_tokens	*tmp;

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

/*	lst_print()
*	print given linked list's contents
*/
void	lst_print(t_tokens *cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\nlst_print:\n");
	while (cmds)
	{
		printf("node %d:\n", j);
		printf("	command: %s\n", cmds->command);
		printf("	options:\n");
		i = 0;
		while (cmds->opt[i])
		{
			printf("		opt[%d]: %s\n", i, cmds->opt[i]);
			i++;
		}
		cmds = cmds->next;
		j++;
	}
}
