/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:16:57 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 18:22:33 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hdpart	*ft_lstnew_hd(char *str, int expand)
{
	t_hdpart	*new;

	new = (t_hdpart *)malloc(sizeof(t_hdpart));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	new->should_expand = expand;
	new->next = NULL;
	return (new);
}

static t_hdpart	*ft_lstlast(t_hdpart *part)
{
	if (part == NULL)
		return (NULL);
	while (part->next != NULL)
		part = part->next;
	return (part);
}

void	ft_lstadd_back_hd(t_hdpart **part, t_hdpart *new)
{
	t_hdpart	*last;

	if (part == NULL || new == NULL)
		return ;
	if (*part == NULL)
		*part = new;
	else
	{
		last = ft_lstlast(*part);
		last->next = new;
	}
}
