/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:38:34 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/02 22:34:18 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	strlen_before_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13) && str[i] != '\0' && str[i] != '"')
		i++;
	return (i);
}