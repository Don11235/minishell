/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:46:03 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/18 15:16:02 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int middle_cases(t_token *current, t_shell *shell)
{
	if (current->type == TOKEN_PIPE && current->next != NULL
		&& current->next->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		shell->last_exit_status = 258;
		return (1);				
	}
	if ((current->type >= 4 && current->type <= 7) && current->next != NULL
		&& (current->next->type >= 3 && current->next->type <= 7))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			current->next->token);
		shell->last_exit_status = 258;
		return (1);
	}
	return (0);
}

int	valid_tokens(t_token *head, t_shell *shell)
{
	t_token *current;

	current = head;
	if (head == NULL)
		return (0);
	if (current->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		shell->last_exit_status = 258;
		return (1);
	}
	while (current != NULL)
	{
		if (middle_cases(current, shell))
			return (1);
		if (current->next == NULL && (current->type >= 3 && current->type <= 7))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			shell->last_exit_status = 258;
			return (1);
		}
		current = current->next;
	}
	return (0);
}
