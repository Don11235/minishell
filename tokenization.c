/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:13:10 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/21 19:51:24 by ytlidi           ###   ########.fr       */
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
	int		len;

	len = ft_strlen(str);
	if (*i >= len)
		return (0);
	while (*i < len && (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	if (*i < len && (str[*i] == '\'' || str[*i] == '"'))
	{
		q = str[*i];
		j = (*i)++;
		flag = 1;
		while (*i < len && inner_word_or_quote_skipping_condition(str, *i, flag, 1))
			inner_word_or_quote_skipping(str, i, &flag, &q);
		if (add_token_string_to_token_list(str, *i, j, list))
			return (1);
		if (*i < len)
			(*i)++;
	}
	return (0);
}

int pipes_and_rds_tokens(char *str, t_token **list, int *i)
{
	char	rd;
	int		len;

	len = ft_strlen(str);
	if (*i < len && (str[*i] == '|' || str[*i] == '>' || str[*i] == '<'))
	{
		rd = str[*i];
		if (*i + 1 < len && str[*i + 1] == rd && rd != '|')
			return (inner_pipes_and_rds_tokens(str, list, i, 2));
		else
			return (inner_pipes_and_rds_tokens(str, list, i, 1));
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
	int		len;

	len = ft_strlen(str);
	j = *i;
	flag = 0;
	while (*i < len && inner_word_or_quote_skipping_condition(str, *i, flag, 0))
		inner_word_or_quote_skipping(str, i, &flag, &q);
	if (*i <= len && add_token_string_to_token_list(str, *i, j, list))
		return (1);
	return (0);
}
