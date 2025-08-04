/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_all_heredoc_fds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:48:42 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 17:06:46 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_all_heredoc_fds(t_command *cmd_list)
{
	t_redirection	*red;

	if (!cmd_list->rds)
		return ;
	while (cmd_list)
	{
		red = cmd_list->rds;
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
		cmd_list = cmd_list->next;
	}
}
