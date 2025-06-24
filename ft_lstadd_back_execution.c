/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:50:09 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/24 23:11:17 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_lstadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (env == NULL || new == NULL)
		return ;
	if (*env == NULL)
		*env = new;
	else
	{
		last = ft_lstlast(*env);
		last->next = new;
	}
}