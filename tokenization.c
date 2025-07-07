/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:13:10 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/06 13:15:40 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_tokens(char *str, t_token **list, int *i)
{
	char	q;
	int		j;
	char	*s;
	t_token	*token;
	int		flag;

	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '"')
	{
		q = str[*i];
		j = *i;
		(*i)++;
		flag = 1;
		while (inner_word_or_quote_skipping_condition(str, *i, flag, 1))
			inner_word_or_quote_skipping(str, i, &flag, &q);
		if (add_token_string_to_token_list(str, *i, j, list))
			return (1);
		(*i)++;
	}
	return (0);
}

int pipes_and_rds_tokens(char *str, t_token **list, int *i)
{
	char	rd;

	if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
	{
		rd = str[*i];
		if (str[*i + 1] == rd && rd != '|')
			return (inner_pipes_and_rds_tokens(str, list, &i, 2));
		else
			return (inner_pipes_and_rds_tokens(str, list, &i, 1));
	}
	return (0);
}

int word_tokens(char *str, t_token **list, int *i)
{
	int		j;
	char	*s;
	char	q;
	t_token *token;
	int		flag;
	   	
	j = *i;
	flag = 0;
	while (inner_word_or_quote_skipping_condition(str, *i, flag, 0))
		inner_word_or_quote_skipping(str, i, &flag, &q);
	if (add_token_string_to_token_list(str, *i, j, list))
		return (1);
	return (0);
}
