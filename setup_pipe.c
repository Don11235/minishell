/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:44:14 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 17:09:33 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe(int *pipefd)
{
	int	result;

	result = pipe(pipefd);
	if (check_fail(result, "pipe error"))
		return (1);
	return (0);
}
