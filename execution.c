/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:58:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/07 18:30:07 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_direct_builtin(t_command *cmd, t_fd_backup *fd_backup,
	t_exec_context *ctx)
{
	if (handle_redirections(cmd->rds))
		return (restore_stdio(fd_backup->saved_stdin, fd_backup->saved_stdout),
			1);
	execute_builtin(cmd, ctx->env, ctx->shell);
	return (0);
}

int	prepare_command(t_command *cmd, t_exec_context *ctx)
{
	ctx->is_builtin = check_builtin(cmd);
	if (!ctx->is_builtin)
	{
		ctx->cmd_path = resolve_command_path(cmd, *(ctx->env), ctx->shell);
		if (!ctx->cmd_path)
		{
			cmd = cmd->next;
			return (1);
		}
	}
	return (0);
}

int	handle_command_exec(t_command *cmd, int *pipefd, int *prev_read_end,
	t_exec_context	*ctx)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (cleanup_fork(pipefd, prev_read_end), 1);
	if (cmd->pid == 0)
	{
		reset_child_state();
		if (handle_pipe_fds(cmd, prev_read_end, pipefd)
			|| handle_redirections(cmd->rds))
			exit(1);
		if (ctx->is_builtin)
			execute_builtin(cmd, ctx->env, ctx->shell);
		else
		{
			if (execve(ctx->cmd_path, cmd->args, env_to_array(*(ctx->env))) == -1)
				(check_fail(-1, ctx->cmd_path), exit(126));
		}
		exit(0);
	}
	else
	{
		if (!ctx->is_builtin)
			free(ctx->cmd_path);
		prepare_next_cmd(cmd, prev_read_end, pipefd);
	}
	return (0);
}

int	execute_loop(t_command *cmd, t_env **env, t_shell *shell,
	t_fd_backup *fd_backup)
{
	int				pipefd[2];
	t_exec_context	ctx;

	init_exec_context(&ctx, env, shell);
	while (cmd)
	{
		if (skip_if_empty(cmd))
			return (1);
		if (prepare_command(cmd, &ctx))
		{
			cmd = cmd->next;
			continue ;
		}
		if ((cmd->pipe_out && setup_pipe(pipefd)))
			return (1);
		if (ctx.is_builtin && !cmd->pipe_in && !cmd->pipe_out)
			return (handle_direct_builtin(cmd, fd_backup, &ctx));
		else
		{
			if (handle_command_exec(cmd, pipefd, &ctx.prev_read_end, &ctx))
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	execute(t_command *cmd_list, t_env **env, t_shell *shell)
{
	t_fd_backup	fd_backup;

	if (init_fd_backup(&fd_backup))
		return (free_cmd_list(cmd_list), 1);
	if (prepare_heredocs(cmd_list, env, shell))
	{
		restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout);
		return (free_cmd_list(cmd_list), 1);
	}
	if (execute_loop(cmd_list, env, shell, &fd_backup))
	{
		restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout);
		wait_for_child(cmd_list, shell);
		return (free_cmd_list(cmd_list), 1);
	}
	restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout);
	wait_for_child(cmd_list, shell);
	return (free_cmd_list(cmd_list), 0);
}
