/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:41:52 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/17 14:37:48 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(t_tokens *tmp)
{
	int	i;
	int	files;

	i = 0;
	files = count_strings(tmp->in) + count_strings(tmp->heredoc);
	while (i < files)
		close(tmp->fd_in[i++]);
	i = 0;
	files = count_strings(tmp->out) + count_strings(tmp->out_app);
	while (i < files)
		close(tmp->fd_out[i++]);
}

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
		close_fds(tmp);
		free(tmp->fd_in);
		free(tmp->fd_out);
		free(tmp->command);
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

int	count_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
