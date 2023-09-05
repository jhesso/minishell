/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:07:36 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/05 12:47:55 by jhesso           ###   ########.fr       */
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
	global.error_code = 0;
}
