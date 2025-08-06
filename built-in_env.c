/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:01:38 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/06 01:00:42 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *env, t_shell *shell)
{
	while (env)
	{
		if (env->value && printf("%s=%s\n", env->key, env->value) == -1)
			return (shell->last_exit_status = 1, 1);
		env = env->next;
	}
	return (shell->last_exit_status = 0, 0);
}
