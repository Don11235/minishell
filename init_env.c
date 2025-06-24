/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:22:07 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/24 23:51:36 by mben-cha         ###   ########.fr       */
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
		printf("++%s++\n", env_list->key);
		free_split(key_value);
		i++;
	}
	return (env_list);
}

int main(int argc, char *argv[], char **envp)
{
	t_env	*env;
	t_env	*tmp;
	
	env = init_env(envp);
	// tmp = env;
	// while (tmp)
	// {
	// 	printf("%s %s\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }
}
