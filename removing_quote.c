/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:45:49 by ytlidi            #+#    #+#             */
/*   Updated: 2025/08/03 21:00:56 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg_word	*remove_quote(t_token *token, t_env *env, t_shell *shell)
{
	int			continue_flag;
	t_env		*env_line;
	t_parsing	*parsing;
	t_arg_word	*arg_word;

	parsing = malloc(sizeof(t_parsing));
	if (parsing == NULL)
		return (NULL);
	remove_quote_func_init(parsing, token, env, shell);
	while (parsing->str[parsing->i] != '\0')
	{
		continue_flag = remove_quote_inner_loop(token, env, shell, parsing);
		if (continue_flag == 1)
			continue ;
		if (parsing->str[parsing->i] == '\0')
			break ;
		parsing->new_str->str[parsing->j++] = parsing->str[parsing->i++];
	}
	parsing->new_str->str[parsing->j] = '\0';
	if (in_case_of_quote_not_closed
		(parsing->new_str->str, parsing->j, parsing->flag))
		return (free(parsing->new_str->str), free(parsing->new_str),
			free(parsing), NULL);
	arg_word = parsing->new_str;
	return (free(parsing), arg_word);
}
