/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quote_marks_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:02:35 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/05 21:13:10 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skipping_if_quote_mark(char *str, int *i, int *flag, char *q)
{
	int	continue_flag;
	
	continue_flag = 0;
	if ((*flag % 2 == 0 && (str[*i] == '\'' || str[*i] == '"'))
		|| (*flag % 2 == 1 && str[*i] == *q))
	{
		*q = str[*i];
		(*flag)++;
		(*i)++;
		continue_flag = 1;
	}
	return (continue_flag);
}

char	*remove_quote_func_init(int *i, t_token *token, char **new_str,
	t_env *env)
{
	char	*str;

	*i = 0;
	if (token->type >= 4 && token->type <= 7)
		str = token->next->token;
	else
		str = token->token;
	*new_str = malloc(calc_new_str_len(str, env) + 1); //free
	return (str);
}

int	in_case_of_quote_not_closed(char *new_str, int j, int flag)
{
	new_str[j] = '\0';
	if (flag % 2 == 1)
	{
		printf("quote not closed\n");
		free(new_str);
		return (1);
	}
	return (0);
}
