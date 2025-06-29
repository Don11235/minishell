/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:46:03 by ytlidi            #+#    #+#             */
/*   Updated: 2025/06/22 16:55:28 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_tokens(t_token *head)
{
	t_token *current;

	current = head;
	if (current->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE && current->next != NULL
			&& current->next->type == TOKEN_PIPE)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);				
		}
		if ((current->type >= 3 && current->type <= 7) && current->next != NULL
			&& (current->next->type >= 4 && current->next->type <= 7))
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				current->next->token);
			return (1);
		}
		if (current->next == NULL && (current->type >= 3 && current->type <= 7))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		current = current->next;
	}
	return (0);
}
