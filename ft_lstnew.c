/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:40:45 by ytlidi            #+#    #+#             */
/*   Updated: 2025/05/28 22:22:35 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(char *token)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node -> token = token;
	new_node -> next = NULL;
	return (new_node);
}