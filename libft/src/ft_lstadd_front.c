/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:48:49 by jhesso            #+#    #+#             */
/*   Updated: 2022/11/18 10:55:02 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL && new != NULL)
		*lst = new;
	else if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
