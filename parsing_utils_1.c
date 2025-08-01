/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:38:34 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/30 13:24:59 by mben-cha         ###   ########.fr       */
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

t_env	*find_env_exp(t_env *env, t_parsing *parsing, int i)
{
	t_env	*tmp;
	char	*str;

	str = parsing->str;
	tmp = env;
	if (!str)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp_exp(&str[i], tmp->key))
		{
			return (tmp);
		}
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
		&& str[i] != '.' && str[i] != ',' && str[i] != ';' && str[i] != ':'
		&& str[i] != ']' && str[i] != '=' && !(str[i] >= '0' && str[i] <= '9')
		&& str[i] != ')')
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

int	calc_new_str_len(t_parsing *parsing, t_env *env, t_shell *shell)
{
	t_env	*env_line;

	int (i), len = 0;
	i = 0;
	while (parsing->str[i] != '\0')
	{
		if (parsing->str[i] == '$')
		{
			i++;
			len++;
			if (parsing->str[i] == '?')
			{
				i++;
				len += ft_strlen(ft_itoa(shell->last_exit_status));
				continue;
			}
			if (parsing->str[i] != '\0')
			{
				parsing->k = i;
				env_line = find_env_exp(env, parsing, i);
				if (env_line != NULL)
					len += ft_strlen(env_line->value);
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return len;
}
