/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:51:28 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/09 17:34:08 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_key_array(t_env *env, t_env **array)
{
	int	i;
	
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	array[i] = NULL;
}

t_env	**get_sorted_env_ptr_array(t_env *env_list)
{
	int		size_env_list;
	t_env	**array;

	size_env_list = env_size(env_list);
	array = malloc((size_env_list + 1) * sizeof(t_env *));
	if (!array)
		return (NULL);
	fill_key_array(env_list, array);
	quick_sort_env(array, 0, size_env_list - 1);
	return (array);
}
