/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_inner_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:14:29 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/31 17:36:52 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_condition(t_parsing *parsing, char q)
{
	int		condition;
	char	*str;
	int		i;
	int		flag;

	str = parsing->str;
	i = parsing->i;
	flag = parsing->flag;
	condition = str[i] == '$' && ((flag % 2 == 1 && q == '"') || flag % 2 == 0);
	return (condition);
}

int	printing_dollar(t_parsing *parsing, t_env *env_line)
{
	int		continue_flag;
	char	*new_str;
	int		j;
	char	*str;
	int		i;

	new_str = parsing->new_str->str;
	j = parsing->j;
	str = parsing->str;
	i = parsing->i;
	if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) || str[i] == '\0'
		|| (parsing->flag == 1 && env_line == NULL && (str[i] == ' '
				|| str[i] == '"')) || str[i] == ':' || str[i] == '=')
	{
		new_str[j] = '$';
		j++;
		continue_flag = 1;
	}
	parsing->new_str->str = new_str;
	parsing->j = j;
	return (continue_flag);
}

int	expand_to_last_exit_status(t_parsing *parsing, t_shell *shell)
{
	int		continue_flag;
	char	*exit_status;
	int		k;
	char	*str;
	char	*new_str;

	str = parsing->str;
	new_str = parsing->new_str->str;
	exit_status = ft_itoa(shell->last_exit_status);
	k = 0;
	if (str[parsing->i] == '?')
	{
		while (exit_status[k] != '\0')
		{
			new_str[parsing->j] = exit_status[k];
			k++;
			parsing->j++;
		}
		parsing->i++;
		continue_flag = 1;
	}
	parsing->str = str;
	parsing->new_str->str = new_str;
	return (free(exit_status), continue_flag);
}

int	expand_to_an_empty_string(t_parsing *parsing, t_env *env_line)
{
	int		continue_flag;
	char	*str;
	int		i;

	str = parsing->str;
	i = parsing->i;
	if (env_line == NULL && str[i - 1] != '?')
	{
		i += strlen_before_spaces_or_delimiter(&str[i]);
		continue_flag = 1;
	}
	parsing->i = i;
	return (continue_flag);
}

int	expand_to_a_real_value(t_parsing *parsing, t_env *env_line)
{
	int		continue_flag;
	char	*new_str;
	int		j;
	int		i;

	new_str = parsing->new_str->str;
	j = parsing->j;
	i = parsing->i;
	if (env_line != NULL)
	{
		expanding(new_str, &j, env_line->value);
		i += ft_strlen(env_line->key);
		continue_flag = 1;
		parsing->new_str->expanded = 1;
	}
	parsing->new_str->str = new_str;
	parsing->j = j;
	parsing->i = i;
	return (continue_flag);
}
