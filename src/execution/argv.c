/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:26:39 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/20 15:26:59 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_argv(t_minihell *minihell)
{
	t_tokens	*temp;
	int			options;
	int			i;

	temp = minihell->lst_tokens;
	while (minihell->lst_tokens != NULL)
	{
		options = count_strings(minihell->lst_tokens->opt);
		minihell->lst_tokens->argv = malloc(sizeof(char *) * (options + 2));
		if (!minihell->lst_tokens->argv)
			malloc_error();
		if (!minihell->lst_tokens->command)
			minihell->lst_tokens->argv[0] = NULL;
		else
		{
			minihell->lst_tokens->argv[0] = ft_strdup(minihell->lst_tokens->command);
			if (!minihell->lst_tokens->argv[0])
				malloc_error();
		}
		i = 0;
		while (minihell->lst_tokens->opt[i])
		{
			minihell->lst_tokens->argv[i + 1] = minihell->lst_tokens->opt[i];
			i++;
		}
		minihell->lst_tokens->argv[i + 1] = NULL;
    	minihell->lst_tokens = minihell->lst_tokens->next;
	}
	minihell->lst_tokens = temp;
}
