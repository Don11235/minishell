/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:22:07 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:22 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	int		i;
	char	**key_value;
	t_env	*new;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		if (key_value == NULL)
			return (NULL);
		new = ft_lstnew(key_value[0], key_value[1]);
		ft_lstadd_back(&env_list, new);
		free(key_value);
		i++;
	}
	return (env_list);
}
