/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:16:52 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/27 12:41:12 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list(t_token *list)
{
	t_token *tmp;

	while (list != NULL)
	{
		free(list->token);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}