/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirections_tokenization_functio        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:26:15 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/06 12:32:08 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void filling_type_pipe_or_rd(t_token *list)
{
	if (list->token[1] == '\0')
	{
		if (list->token[0] == '|')
			list->type = TOKEN_PIPE;
		if (list->token[0] == '>')
			list->type = TOKEN_RD_OUT;
		if (list->token[0] == '<')
			list->type = TOKEN_RD_IN;
	}
	else
	{
		if (list->token[1] == '>')
			list->type = TOKEN_APPEND;
		if (list->token[1] == '<')
			list->type = TOKEN_HEREDOC;
	}
}

int inner_pipes_and_rds_tokens(char *str, t_token **list, int **i, int s_or_d)
{
	char 	*s;
	int		j;
	t_token	*token;

	s = malloc(s_or_d + 1); //freed
	if (s == NULL)
		return (1);
	j = 0;
	while (j < s_or_d)
	{
		s[j] = str[**i];
		j++;
	}
	s[j] = '\0';
	token = ft_lstnew_token(s); //free
	filling_type_pipe_or_rd(token);
	ft_lstadd_back_token(list, token);
	**i += s_or_d;
	free(s);
	return (0);
}