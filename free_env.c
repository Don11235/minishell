/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:25:32 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/27 21:25:41 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_env(t_env *env_list)
{
    t_env   *tmp;

    while (env_list)
    {
        free(env_list->key);
        free(env_list->value);
        tmp = env_list;
        env_list = env_list->next;
        free(tmp);
    }
}