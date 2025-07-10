/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:58:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/10 22:30:14 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_fds(t_command *cmd, int *pipefd)
{
	int	ret;

	if (cmd->pipe_out)
	{
		ret = dup2(pipefd[1], STDOUT_FILENO);
		if (check_fail(ret, "pipe write"))
			return (1);
		close(pipefd[1]);
	}
	else
		close(pipefd[1]);
	if (cmd->pipe_in)
	{
		if (close(pipefd[0]) == -1)
			perror("pipefd[0] already closed?");
		ret = dup2(pipefd[0], STDIN_FILENO);
		if (check_fail(ret, "pipe read"))
			return (1);
		close(pipefd[0]);
	}
	else
		close(pipefd[0]);
	return (0);
}

int	prepare_heredocs(t_command *cmd)
{
	t_redirection	*redirect;
	int				pipefd[2];
	char			*line;

	while (cmd)
	{
		redirect = cmd->rds;
		while (redirect)
		{
			if (redirect->type == TOKEN_HEREDOC)
			{
				if (cmd->heredoc_fd != -1)
					close(pipefd[0]);
				if (setup_pipe(pipefd))
					return (1);
				while (1)
				{
					line = readline("> ");
					if (!line || line == redirect->filename_or_delimiter)
					{
						free(line);
						break ;
					}
					ft_putstr_fd(line, pipefd[1]);
					free(line);
				}
				close(pipefd[1]);
				cmd->heredoc_fd = pipefd[0];
			}
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	execute(t_command *cmd_list, t_env *env, t_shell *shell)
{
	t_command	*cmd;
	t_fd_backup	*fd_backup;
	pid_t		pid;
	int			pipefd[2];
	int			is_built_in;
	char		*cmd_path;
	int			status;

	cmd = cmd_list;
	while (cmd)
	{
		is_built_in = check_builtin(cmd);
		if (!is_built_in)
			cmd_path = resolve_command_path(cmd, env);
		if (!cmd_path)
			return (1);
		if (cmd->pipe_out && setup_pipe(pipefd))
			return (1);
		if (is_built_in && !cmd->pipe_out)
		{
			fd_backup = handle_redirections(cmd);
			if (!fd_backup)
				return (1);
			execute_builtin(cmd, env, shell);
			if (fd_backup->has_redirection)
			{				
				restore_stdio(fd_backup->saved_stdin, fd_backup->saved_stdout);
				free(fd_backup);
			}
		}
		else
		{
			pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
				if (handle_pipe_fds(cmd, pipefd))
					return (1);
				fd_backup = handle_redirections(cmd);
				if (!fd_backup)
					return (1);
				if (is_built_in)
					execute_builtin(cmd, env, shell);
				else
					execve(cmd_path, cmd->args, env_to_array(env));
			}
			// else
			// {
			// 	close(pipefd[0]);
			// 	close(pipefd[1]);
			// }
		}
		cmd = cmd->next;
	}
	wait(&status);
	return (0);
}
