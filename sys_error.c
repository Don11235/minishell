/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syscall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:52:59 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/25 04:07:57 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_or_exit(int result, char *msg)
{
	if (result == -1)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

