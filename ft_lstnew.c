/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:40:45 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/25 13:39:05 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(char *token)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node -> token = token;
	new_node -> next = NULL;
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
	new_node -> is_delimiter_quoted = 0;
	new_node -> filename_or_delimiter = filename_or_delimiter;
	new_node -> heredoc_fd = -1;
	new_node -> next = NULL;
	return (new_node);
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
