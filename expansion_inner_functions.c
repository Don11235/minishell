/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_inner_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:14:29 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/16 11:17:43 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_condition(char *str, int i, int flag, char q)
{
	int	condition;

	condition = str[i] == '$' && ((flag % 2 == 1 && q == '"') || flag % 2 == 0);
	return (condition);
}

int	printing_dollar(char *new_str, int *j, char *str, int *i)
{
	int	continue_flag;
	
	(*i)++;
	if ((str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		|| str[*i] == '\0' || str[*i] == '"')
	{
		new_str[*j] = '$';
		(*j)++;
		continue_flag = 1;
	}
	return (continue_flag);
}

int expand_to_last_exit_status(char *new_str, int *j, char *str, int *i, t_shell *shell)
{
	int 	continue_flag;
	char	*exit_status;
	int		k;

	exit_status = ft_itoa(shell->last_exit_status);
	k = 0;
	if (str[*i] == '?')
	{
		while (exit_status[k] != '\0')
		{
			new_str[*j] = exit_status[k];
			k++;
			(*j)++;
		}
		(*i)++;
		continue_flag = 1;
	}
	return (continue_flag);
}

int	expand_to_an_empty_string(char *str, int *i, t_env *env_line, int *flag)
{
	int	continue_flag;

	if (env_line == NULL && str[*i - 1] != '?')
	{
		*i += strlen_before_spaces_or_delimiter(&str[*i]);
		continue_flag = 1;
	}
	return (continue_flag);
}

int	expand_to_a_real_value(char *new_str, int *j, int *i, t_env *env_line)
{
	int	continue_flag;

	if (env_line != NULL)
	{
		expanding(new_str, j, env_line->value);
		*i += ft_strlen(env_line->key);
		continue_flag = 1;
	}
	return (continue_flag);
}
