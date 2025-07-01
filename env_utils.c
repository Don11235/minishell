/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:09:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/27 19:53:24 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	if (!key)
		return (NULL);
	while (tmp)
	{
		if (!strcmp(key, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	update_env(t_env *env, char *key, char *new_value)
{
	t_env	*env_node;

	env_node = find_env(env, key);
	if (!env_node)
		return (1);
	free(env_node->value);
	env_node->value = ft_strdup(new_value);
	if (!env_node->value)
		return (1);
	return (0);
}

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	if (!env)
		return ;
	new_node = ft_lstnew(key, value);
	if (new_node)
		return ;
	ft_lstadd_back(env, new_node);
}
