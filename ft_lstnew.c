/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:40:45 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/01 20:47:41 by ytlidi           ###   ########.fr       */
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
	new_node -> pipe_in = 0;
	new_node -> pipe_out = 0;
	new_node -> rds = NULL;
	new_node -> next = NULL;
	return (new_node);
}

t_redirection *ft_lstnew_redirection(int type, char *filename_or_delimiter)
{
	t_redirection *new_node;

	new_node = malloc(sizeof(t_redirection));
	new_node -> type = type;
	new_node -> filename_or_delimiter = filename_or_delimiter;
	new_node -> next = NULL;
	return (new_node);
}
