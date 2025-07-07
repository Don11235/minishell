/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:38:34 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/06 12:47:57 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expanding(char *new_str, int *j, char *str_to_add)
{
	int	i;

	i = 0;
	while (str_to_add[i] != '\0')
	{
		new_str[*j] = str_to_add[i];
		i++;
		(*j)++;
	}
}

t_env	*find_env_exp(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp_exp(key, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	strlen_before_spaces_or_delimiter(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13) && str[i] != '\0'
		&& str[i] != '/' && str[i] != '$' && str[i] != '"' && str[i] != '\''
		&& str[i] != '.' && str[i] != ',' && str[i] != ';' && str[i] != ':')
		i++;
	return (i);
}

int words_count(t_token *beginning)
{
	int		i;
	t_token	*current;

	current = beginning;
	i = 0;
	while (current != NULL && current->type != TOKEN_PIPE)
	{
		if (current->type >= 4 && current->type <= 7)
			current = current->next->next;
		else
			current = current->next;
		i++;
	}
	return i;
}

int	calc_new_str_len(char *str, t_env *env)
{
	int	i;
	int len;
	t_env	*env_line;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			len++;
			env_line = find_env_exp(env, &str[i]);
			if (env_line != NULL)
				len += ft_strlen(env_line->value);
		}
		i++;
		len++;
	}
	return len;
}
