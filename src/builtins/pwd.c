/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:07:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/08/31 23:53:42 by dardangergu      ###   ########.fr       */
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
	error_code = 0;
}
