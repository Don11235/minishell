/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hd_parts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 03:44:10 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 16:41:42 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_hd_parts(t_hdpart *part)
{
	t_hdpart	*tmp;

	while (part != NULL)
	{
		free(part->str);
		tmp = part;
		part = part->next;
		free(tmp);
	}
}
