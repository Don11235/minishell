/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_heredoc_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:47:30 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/01 19:48:12 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_heredoc_fd(t_command *cmd)
{
	t_redirection	*red;

		red = cmd->rds;
		while (red)
		{
			if (red->type == TOKEN_HEREDOC && red->heredoc_fd != -1)
			{
				close(red->heredoc_fd);
				red->heredoc_fd = -1;
			}
			else
				break ;
			red = red->next;
		}
}