/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:11:40 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/31 20:46:30 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unquoted(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0' && token[i] != '"' && token[i] != '\'')
		i++;
	if (token[i] == '"' || token[i] == '\'')
		return (0);
	return (1);
}

static void	calc_env_expanding(t_env *env, t_parsing *parsing, int i, int *len)
{
	t_env	*env_line;

	env_line = find_env_exp(env, parsing, i);
	if (env_line != NULL)
		*len += ft_strlen(env_line->value);
}

static int	calc_exit_status_expanding(t_shell *shell, int *len)
{
	int		continue_flag;
	char	*last_exit_status;

	last_exit_status = ft_itoa(shell->last_exit_status);
	*len += ft_strlen(last_exit_status);
	free(last_exit_status);
	continue_flag = 1;
	return (continue_flag);
}

int	calc_new_str_len(t_parsing *parsing, t_env *env, t_shell *shell)
{
	int (i), (continue_flag), len = 0;
	i = 0;
	while (parsing->str[i] != '\0')
	{
		continue_flag = 0;
		if (parsing->str[i] == '$')
		{
			i++;
			len++;
			if (parsing->str[i] == '?')
				continue_flag = calc_exit_status_expanding(shell, &len);
			if (continue_flag == 1)
				continue ;
			if (parsing->str[i] != '\0')
				calc_env_expanding(env, parsing, i, &len);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}