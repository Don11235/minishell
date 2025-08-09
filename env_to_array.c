/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:52:28 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/09 06:32:00 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_env_var(char *s1, char *s2, char sep)
{
	size_t	len;
	size_t	len1;
	char	*pt;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len = len1 + ft_strlen(s2);
	pt = (char *)malloc((len + 2) * sizeof(char));
	if (pt == NULL)
		return (NULL);
	ft_memcpy(pt, s1, len1);
	pt[len1] = sep;
	ft_memcpy(pt + len1 + 1, s2, ft_strlen(s2));
	pt[len + 1] = '\0';
	return (pt);
}

char	**env_to_arr(t_env *env)
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
		env_array[i] = join_env_var(env->key, env->value, '=');
		if (!env_array[i])
			return (NULL);
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
