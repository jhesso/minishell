/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:22:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/20 15:32:39 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	free_list()
*	frees the lst_tokens linked list and all of its contents
*/
static void	free_list(t_tokens *lst_tokens)
{
	t_tokens	*tmp;

	while (lst_tokens)
	{
		tmp = lst_tokens;
		lst_tokens = lst_tokens->next;
		free(tmp->command);
		if (tmp->fd_in > 0)
			close(tmp->fd_in);
		if (tmp->fd_out > 0)
			close(tmp->fd_out);
		free_str_arr(tmp->opt);
		free_str_arr(tmp->in);
		free_str_arr(tmp->out);
		free_str_arr(tmp->out_app);
		free_str_arr(tmp->heredoc);
		free(tmp->argv[0]);
		free(tmp->argv);
		free(tmp);
	}
}

/*	cleanup()
*	frees all the allocated memory in preparation
*	for the next command line
*	note, does not free env as we need it until the end
*/
void	cleanup(t_minihell *minihell)
{
	free_list(minihell->lst_tokens);
	free_str_arr(minihell->tokens);
}

/*	free_str_arr()
*	frees a 2d array of strings (char **)
*	param: char **ret, int row
*	return: NULL (always)
*/
void	*free_str_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	if (s)
		free(s);
	return (NULL);
}
