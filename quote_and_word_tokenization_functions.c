/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_word_tokenization_functions.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:55:56 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/05 20:10:51 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inner_word_or_quote_skipping_condition(char *str, int i, int flag, int type)
{
	int	condition;

	if (type == 0)
		condition = ((str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)
			&& str[i] != '|' && str[i] != '>' && str[i] != '<')
			|| flag % 2 == 1) && str[i] != '\0';
	else if (type == 1)
		condition = ((str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
			|| flag % 2 == 1) && str[i] != '\0';
	return condition;
}

void	inner_word_or_quote_skipping(char *str, int *i, int *flag, char *q)
{
	if ((*flag % 2 == 0 && (str[*i] == '\'' || str[*i] == '"'))
		|| (*flag % 2 == 1 && str[*i] == *q))
	{
		*q = str[*i];
		(*flag)++;
	}
	(*i)++;		
}
void filling_type_s_or_d_quote(t_token *list)
{
	if (list->token[0] == '\'')
		list->type = TOKEN_S_QUOTE;
	if (list->token[0] == '"')
		list->type = TOKEN_D_QUOTE;
}

int	add_token_string_to_token_list(char *str, int i, int j, t_token **list)
{
	char	*s;
	t_token	*token;
	
	if (i > j)
	{
		s = ft_substr(str, j, i - j); //free
		if (s == NULL)
			return (1);
		token = ft_lstnew_token(s); //free
		if (str[j] == '"' || str[j] == '\'')
			filling_type_s_or_d_quote(token);
		else
			token->type = TOKEN_WORD; //not necessary (it's 0 by default)
		ft_lstadd_back_token(list, token);
	}
	return (0);
}
