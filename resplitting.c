/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resplittting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:49:03 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/31 23:16:21 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_count(char **args, t_token **list)
{
	int		i;
	t_token	*node;

	i = 0;
	while (args[i] != NULL)
	{
		node = ft_lstnew_token(args[i]);
		if (node == NULL)
			return (i);
		ft_lstadd_back_token(list, node);
		i++;
	}
	return (i);
}

int	in_case_of_type_less_than_3(t_token *current_token, t_env *env,
	t_shell *shell, t_token **list)
{
	t_arg_word	*quote_removed;
	char		**array;
	int			counter;
	t_token		*node;

	counter = 0;
	quote_removed = remove_quote(current_token, env, shell);
	if (quote_removed == NULL)
		return (-1);
	if (quote_removed->expanded == 1)
	{
		array = ft_split_whitespace(quote_removed->str);
		counter += array_count(array, list);
		free_split(array);
	}
	else
	{
		node = ft_lstnew_token(quote_removed->str);
		ft_lstadd_back_token(list, node);
		counter++;
	}
	return (free(quote_removed->str), free(quote_removed), counter);
}

int	args_count(t_token *current_token, t_env *env,
	t_shell *shell, t_token **list)
{
	int	counter;
	int	return_value;

	counter = 0;
	while (current_token != NULL && current_token->type != TOKEN_PIPE)
	{
		if (current_token != NULL && current_token->type < 3)
		{
			return_value = in_case_of_type_less_than_3(current_token, env,
					shell, list);
			if (return_value == -1)
				return (-1);
			counter += return_value;
			current_token = current_token->next;
		}
		else if (current_token->type >= 4 && current_token->type <= 7)
			current_token = current_token->next->next;
	}
	return (counter);
}

void	list_to_args(t_token *list, char **args)
{
	int		i;

	i = 0;
	while (list != NULL)
	{
		args[i] = ft_strdup(list->token);
		list = list->next;
		i++;
	}
	args[i] = NULL;
}
