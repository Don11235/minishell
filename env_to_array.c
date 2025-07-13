/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:52:28 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/07 20:39:24 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env *env)
{
	int		size;
	int		i;
	char	**env_array;

	i = 0;
	size = env_size(env);
	env_array = malloc((size + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (env)
	{
		env_array[i] = ft_strjoin_with(env->key, env->value, '=');
		if (!env_array[i])
				return (NULL); //free
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
