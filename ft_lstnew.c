/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:40:45 by ytlidi            #+#    #+#             */
/*   Updated: 2025/06/14 18:09:21 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(char *token)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node -> token = token;
	new_node -> next = NULL;
	// new_node -> prev = NULL;
	return (new_node);
}

t_command *ft_lstnew_command(char **args)
{
	t_command *new_node;

	new_node = malloc(sizeof(t_command));
	new_node -> args = args;
	new_node -> next = NULL;
	return (new_node);
}

t_redirection *ft_lstnew_redirection(int type, char *file)
{
	t_redirection *new_node;

	new_node = malloc(sizeof(t_redirection));
	new_node -> type = type;
	new_node -> file = file;
	new_node -> next = NULL;
	return (new_node);
}
