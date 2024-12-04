/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:48:22 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/29 17:00:20 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		(del)((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
