/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:18:34 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/31 19:26:27 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_child(t_command *cmd, t_shell *shell)
{
	int	sig;
	int	status;

	while (cmd)
	{
		if (cmd->pid > 0)
		{
			if (waitpid(cmd->pid, &status, 0) == -1)
				return (check_fail(-1, "waitpid"));
		}
		if (!cmd->next && cmd->pid > 0)
		{
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
				{
					shell->last_exit_status = 128 + sig;
					write(1, "Quit: 3\n", 8);
				}
				else if (sig == SIGINT)
				{
					shell->last_exit_status = 128 + sig;
					write(1, "\n", 1);
				}
			}
			else
				shell->last_exit_status = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	} 
	return (0);
}
