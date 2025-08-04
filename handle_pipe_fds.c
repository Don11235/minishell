/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:45:30 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/02 23:20:41 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_fds(t_command *cmd, int *prev_read_end, int *pipefd)
{
	int	ret;

	if (cmd->pipe_in && *prev_read_end != -1)
	{
		ret = dup2(*prev_read_end, STDIN_FILENO);
		if (check_fail(ret, "pipe read"))
			return (1); 
		close(*prev_read_end);
	}
	if (cmd->pipe_out)
	{
		ret = dup2(pipefd[1], STDOUT_FILENO);
		if (check_fail(ret, "pipe write"))
			return (1);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (0);
}