/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quote_marks_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:02:35 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/18 19:28:15 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skipping_if_quote_mark(t_parsing *parsing, char *q)
{
	int		continue_flag;
	char	*str;
	int		i;
	int		flag;

	str = parsing->str;
	i = parsing->i;
	flag = parsing->flag;
	continue_flag = 0;
	if ((flag % 2 == 0 && (str[i] == '\'' || str[i] == '"'))
		|| (flag % 2 == 1 && str[i] == *q))
	{
		*q = str[i];
		flag++;
		i++;
		continue_flag = 1;
	}
	parsing->i = i;
	parsing->flag = flag;
	return (continue_flag);
}

void	remove_quote_func_init(t_parsing *parsing, t_token *token, t_env *env)
{
	char	*new_str;

	parsing->i = 0;
	parsing->j = 0;
	parsing->flag = 0;
	if (token->type >= 4 && token->type <= 7)
		parsing->str = token->next->token;
	else
		parsing->str = token->token;
	new_str = malloc(calc_new_str_len(parsing, env) + 1); //free
	if (new_str == NULL)
		return ;
	parsing->new_str = new_str;
}

int	remove_quote_inner_loop(t_token *token, t_env *env, t_shell *shell, t_parsing *parsing)
{
	int		continue_flag;
	char	q;
	t_env	*env_line;

	continue_flag = skipping_if_quote_mark(parsing, &q);
	if (expand_condition(parsing, q) && token->type != TOKEN_HEREDOC)
	{
		continue_flag = printing_dollar(parsing);
		continue_flag = expand_to_last_exit_status(parsing, shell);
		env_line = find_env_exp(env, parsing);
		continue_flag = expand_to_an_empty_string(parsing, env_line);
		continue_flag = expand_to_a_real_value(parsing, env_line);
	}
	return (continue_flag);	
}

int	in_case_of_quote_not_closed(char *new_str, int j, int flag)
{
	if (flag % 2 == 1)
	{
		printf("quote not closed\n");
		free(new_str);
		return (1);
	}
	return (0);
}
