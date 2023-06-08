/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:15:48 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/14 19:06:26 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_list	*create_node(t_list *lst, t_list *head, void *(*f) (void *), \
								void (*del)(void *))
{
	t_list	*map;

	map = ft_lstnew(f(lst->content));
	if (map == NULL)
	{
		ft_lstclear(&head, del);
		return (NULL);
	}
	return (map);
}

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*head;
	t_list	*tail;

	if (lst == NULL)
		return (NULL);
	head = NULL;
	map = ft_lstnew(f(lst->content));
	if (map == NULL)
		return (NULL);
	ft_lstadd_back(&head, map);
	tail = head;
	lst = lst->next;
	while (lst != NULL)
	{
		map = create_node(lst, head, f, del);
		if (map == NULL)
			return (NULL);
		ft_lstadd_back(&tail, map);
		tail = tail->next;
		lst = lst->next;
	}
	return (head);
}
