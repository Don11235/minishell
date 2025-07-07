/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:19:54 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/07 20:51:16 by ytlidi           ###   ########.fr       */
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

static t_env	*ft_lstlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_lstadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (env == NULL || new == NULL)
		return ;
	if (*env == NULL)
		*env = new;
	else
	{
		last = ft_lstlast(*env);
		last->next = new;
	}
}