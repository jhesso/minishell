/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:07:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/13 19:42:11 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_minihell *minihell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = get_value(ft_strdup("$PWD="), 5, minihell->env);
	if (pwd == NULL)
		malloc_error();
	printf("%s\n", pwd);
	free(pwd);
	minihell->error_code = 0;
}
