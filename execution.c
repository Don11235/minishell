/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:58:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/03 00:38:57 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_pipe_fds(t_command *cmd, int prev_read_end, int *pipefd)
// {
// 	int	ret;

// 	if (cmd->pipe_in && prev_read_end != -1)
// 	{
// 		ret = dup2(prev_read_end, STDIN_FILENO);
// 		if (check_fail(ret, "pipe read"))
// 			return (1); 
// 		close(prev_read_end);
// 	}
// 	if (cmd->pipe_out)
// 	{
// 		ret = dup2(pipefd[1], STDOUT_FILENO);
// 		if (check_fail(ret, "pipe write"))
// 			return (1);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 	}
// 	return (0);
// }

// void	reset_heredoc_fd(t_command *cmd)
// {
// 	t_redirection	*red;

// 		red = cmd->rds;
// 		while (red)
// 		{
// 			if (red->type == TOKEN_HEREDOC && red->heredoc_fd != -1)
// 			{
// 				close(red->heredoc_fd);
// 				red->heredoc_fd = -1;
// 			}
// 			else
// 				break ;
// 			red = red->next;
// 		}
// }

// void	reset_all_heredoc_fds(t_command *cmd_list)
// {
// 	t_redirection	*red;

// 	if (!cmd_list->rds)
// 		return ;
// 	while (cmd_list)
// 	{
// 		red = cmd_list->rds;
// 		while (red)
// 		{
// 			if (red->type == TOKEN_HEREDOC && red->heredoc_fd != -1)
// 			{
// 				close(red->heredoc_fd);
// 				red->heredoc_fd = -1;
// 			}
// 			else
// 				break ;
// 			red = red->next;
// 		}
// 		cmd_list = cmd_list->next;
// 	}
// }

// int	prepare_heredocs(t_command *cmd, t_env *env, t_shell *shell)
// {
// 	t_redirection	*redirect;
// 	t_command		*cmd_list;
// 	pid_t			pid;
// 	int				pipefd[2];
// 	char			*line;
// 	char			*final_line;
// 	int				status;

// 	cmd_list = cmd;
// 	while (cmd)
// 	{
// 		redirect = cmd->rds;
// 		while (redirect)
// 		{
// 			if (redirect->type == TOKEN_HEREDOC)
// 			{
// 				if (setup_pipe(pipefd))
// 					return (1);
// 				pid = fork();
// 				if (pid == -1)
// 					return (1);
// 				if (pid == 0)
// 				{
// 					set_signal(SIGINT, SIG_DFL);
// 					while (1)
// 					{
// 						line = readline("> ");
// 						if (!line || !ft_strcmp(line, redirect->filename_or_delimiter))
// 						{
// 							free(line);
// 							exit(0);
// 						}
// 						if (redirect->is_delimiter_unquoted)
// 						{
// 							final_line = heredoc_expand_line(env, line, shell);
// 							ft_putstr_fd(final_line, pipefd[1]);
// 							free(final_line);
// 						}
// 						else
// 							ft_putstr_fd(line, pipefd[1]);
// 						free(line);
// 					}
// 					exit(0);
// 				}
// 				else
// 				{
// 					set_signal(SIGINT, SIG_IGN);
// 					close(pipefd[1]);
// 					if (waitpid(pid, &status, 0) == -1)
// 						return (check_fail(-1, "waitpid"));
// 					if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 					{
// 						close(pipefd[0]);
// 						write(1, "\n", 1);
// 						reset_all_heredoc_fds(cmd_list);
// 						shell->last_exit_status = 1;
// 						return (1);
// 					}
// 					redirect->heredoc_fd = pipefd[0];
// 				}
// 			}
// 			redirect = redirect->next;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }

int skip_if_empty(t_command *cmd, t_fd_backup *fd_backup)
{
	if (!cmd->args[0])
	{
		handle_redirections(cmd->rds);
		restore_stdio(fd_backup->saved_stdin, fd_backup->saved_stdout);
		return (1);
	}
	return (0);
}

void reset_child_state(void)
{
	restore_termios();
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
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

int	handle_direct_builtin(t_command *cmd, t_fd_backup *fd_backup, t_exec_context *ctx)
{
	if (handle_redirections(cmd->rds))
		return (restore_stdio(fd_backup->saved_stdin, fd_backup->saved_stdout), 1);
	execute_builtin(cmd, ctx->env, ctx->shell);		
	return (0);
}

int	prepare_command(t_command *cmd, t_exec_context *ctx)
{
	ctx->is_builtin = check_builtin(cmd);
	if (!ctx->is_builtin)
	{
		ctx->cmd_path = resolve_command_path(cmd, ctx->env, ctx->shell);
		if (!ctx->cmd_path)
		{
			cmd = cmd->next;
			return (1) ;
		}
	}
	return (0);
}

int	handle_command_exec(t_command *cmd, int *pipefd, int *prev_read_end, t_exec_context	*ctx)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
		reset_child_state();
		if (handle_pipe_fds(cmd, prev_read_end, pipefd) || handle_redirections(cmd->rds))
			exit(1);
		if (ctx->is_builtin)
			execute_builtin(cmd, ctx->env, ctx->shell);
		else
		{
			if (execve(ctx->cmd_path, cmd->args, env_to_array(ctx->env)) == -1)
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

void init_exec_context(t_exec_context *ctx, t_env *env, t_shell *shell)
{
	ctx->env = env;
	ctx->shell = shell;
	ctx->prev_read_end = -1;
}


int execute_loop(t_command *cmd, t_env *env, t_shell *shell, t_fd_backup *fd_backup)
{
	int pipefd[2];
	t_exec_context	ctx;

	init_exec_context(&ctx, env, shell);
	while (cmd)
	{
		if (skip_if_empty(cmd, fd_backup))
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

int	execute(t_command *cmd_list, t_env *env, t_shell *shell)
{
	t_fd_backup	fd_backup;

	if (init_fd_backup(&fd_backup) || prepare_heredocs(cmd_list, env, shell))
		return (1);
	if (execute_loop(cmd_list, env, shell, &fd_backup))
		return (1);
	restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout);
	wait_for_child(cmd_list, shell);
	return (free_cmd_list(cmd_list), 0);
}

// int	execute(t_command *cmd_list, t_env *env, t_shell *shell)
// {
// 	t_command	*cmd;
// 	t_fd_backup	fd_backup;
// 	pid_t		pid;
// 	int			pipefd[2];
// 	int			is_built_in;
// 	char		*cmd_path;
// 	int			status;
// 	int			prev_read_end = -1;
// 	int			sig;


// 	cmd = cmd_list;
// 	if (init_fd_backup(&fd_backup))
// 		return (1);
// 	if (prepare_heredocs(cmd, env, shell))
// 		return (1);
// 	while (cmd)
// 	{
// 		if (!cmd->args[0])
// 		{
// 			handle_redirections(cmd->rds);
// 			restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout);
// 			return (1);
// 		}
// 		is_built_in = check_builtin(cmd);
// 		if (!is_built_in)
// 		{
// 			cmd_path = resolve_command_path(cmd, env, shell);
// 			if (!cmd_path)
// 			{
// 				cmd = cmd->next;
// 				continue ;
// 			}
// 		}
// 		if (cmd->pipe_out && setup_pipe(pipefd))
// 			return (1);
// 		if (is_built_in && !cmd->pipe_in && !cmd->pipe_out)
// 		{
// 			if (handle_redirections(cmd->rds))
// 				return (restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout), 1);
// 			execute_builtin(cmd, env, shell);		
// 		}
// 		else
// 		{
// 			pid = fork();
// 			if (pid == -1)
// 				return (1);
// 			cmd->pid = pid;
// 			if (pid == 0)
// 			{
// 				restore_termios();
// 				set_signal(SIGINT, SIG_DFL);
// 				set_signal(SIGQUIT, SIG_DFL);
// 				if (handle_pipe_fds(cmd, prev_read_end, pipefd))
// 					exit(1);
// 				if (handle_redirections(cmd->rds))
// 					exit(1);
// 				if (is_built_in)
// 					execute_builtin(cmd, env, shell);
// 				else
// 				{
// 					if (execve(cmd_path, cmd->args, env_to_array(env)) == -1)
// 					{
// 						check_fail(-1, cmd_path);
// 						exit(126);
// 					}
// 				}
// 				exit(0);
// 			}
// 			else
// 			{	
// 				set_signal(SIGINT, SIG_IGN);
// 				reset_heredoc_fd(cmd);
// 				if (!is_built_in)
// 					free(cmd_path);
// 				if (prev_read_end != -1)
// 					close(prev_read_end);
// 				if (cmd->pipe_out)
// 				{
// 					close(pipefd[1]);
// 					prev_read_end = pipefd[0];
// 				}
// 				else
// 					prev_read_end = -1;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// 	restore_stdio(fd_backup.saved_stdin, fd_backup.saved_stdout);
// 	wait_for_child(cmd_list, shell);
// 	// while (wait(&status) > 0);
// 	// if (WIFSIGNALED(status))
// 	// {
// 	// 	sig = WTERMSIG(status);
// 	// 	if (sig == SIGQUIT)
// 	// 	{
// 	// 		shell->last_exit_status = 128 + sig;
// 	// 		write(1, "Quit: 3\n", 8);
// 	// 	}
// 	// 	else if (sig == SIGINT)
// 	// 	{
// 	// 		shell->last_exit_status = 128 + sig;
// 	// 		write(1, "\n", 1);
// 	// 	}
// 	// }
// 	// else
// 	// 	shell->last_exit_status = WEXITSTATUS(status);
// 	return (free_cmd_list(cmd_list), 0);
// }
