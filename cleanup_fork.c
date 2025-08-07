/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:27:44 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/07 16:30:36 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_fork(int *pipefd, int *prev_read_end)
{
	if (*prev_read_end != -1)
		close(*prev_read_end);
	close(pipefd[0]);
	close(pipefd[1]);
}