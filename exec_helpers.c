/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:03:38 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/07 14:25:16 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec_context(t_exec_context *ctx, t_env **env, t_shell *shell)
{
	ctx->env = env;
	ctx->shell = shell;
	ctx->prev_read_end = -1;
}

void	reset_child_state(void)
{
	restore_termios();
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
}

int	skip_if_empty(t_command *cmd)
{
	if (!cmd->args[0])
	{
		handle_redirections(cmd->rds);
		return (1);
	}
	return (0);
}

void	prepare_next_cmd(t_command *cmd, int *prev_read_end, int *pipefd)
{
	set_signal(SIGINT, SIG_IGN);
	reset_heredoc_fd(cmd);
	if (*prev_read_end != -1)
		close(*prev_read_end);
	if (cmd->pipe_out)
	{
		close(pipefd[1]);
		*prev_read_end = pipefd[0];
	}
	else
		*prev_read_end = -1;
}
