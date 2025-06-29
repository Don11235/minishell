/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:19:54 by ytlidi            #+#    #+#             */
/*   Updated: 2025/06/21 17:02:09 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*current;

	current = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current -> next != NULL)
			current = current -> next;
		current -> next = new;
	}
	new -> next = NULL;
}

void	ft_lstadd_back_command(t_command **lst, t_command *new)
{
	t_command	*current;

	current = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current -> next != NULL)
			current = current -> next;
		current -> next = new;
	}
	new -> next = NULL;
}

void	ft_lstadd_back_redirection(t_redirection ***lst, t_redirection *new)
{
	t_redirection	*current;

	current = **lst;
	if (new == NULL)
		return;
	if (**lst == NULL)
		**lst = new;
	else
	{
		while (current -> next != NULL)
			current = current -> next;
		current -> next = new;
	}
	new -> next = NULL;
}