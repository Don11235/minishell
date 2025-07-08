/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:58:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/08 13:34:30 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_fds(t_command *cmd, int *pipefd)
{
	int	ret1;
	int	ret2;

	if (cmd->pipe_out)
	{
		ret1 = dup2(pipefd[1], STDOUT_FILENO);
		if (check_fail(ret1, "dup2"))
			return (1);
		close(pipefd[1]);
	}
	else
		close(pipefd[1]);
	if (cmd->pipe_in)
	{
		ret2 = dup2(pipefd[0], STDIN_FILENO);
		if (check_fail(ret2, "dup2"))
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
				if (setup_pipe(pipefd) == -1)
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

t_fd_backup	*handle_redirections(t_command *cmd)
{
	if (!cmd->rds)
		return (NULL);
	t_redirection	*redirect;
	t_fd_backup		*fd_backup;

	fd_backup = malloc(sizeof(t_fd_backup));
	if (!fd_backup)
		return (NULL);
	fd_backup->saved_stdin = dup(STDIN_FILENO);
	if (check_fail(fd_backup->saved_stdin, "dup"))
	{
		free(fd_backup);
		return (NULL);
	}
	fd_backup->saved_stdout = dup(STDOUT_FILENO);
	if (check_fail(fd_backup->saved_stdout, "dup"))
	{
		close (fd_backup->saved_stdin);
		free(fd_backup);
		return (NULL);
	}
	redirect = cmd->rds;
	while (redirect)
	{
		if (redirect->type == TOKEN_RD_IN)
			setup_redirections(TOKEN_RD_IN, redirect->filename_or_delimiter);
		else if (redirect->type == TOKEN_RD_OUT)
			setup_redirections(TOKEN_RD_OUT, redirect->filename_or_delimiter);
		else if (redirect->type == TOKEN_APPEND)
			setup_redirections(TOKEN_APPEND, redirect->filename_or_delimiter);
		redirect = redirect->next;
	}
	return (fd_backup);
}

int	execute(t_command *cmd_list, t_env *env, t_shell *shell)
{
	t_command	*cmd;
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
			cmd_path = resolve_command_path(cmd);
		if (!cmd_path)
			return (1);
		if (cmd->pipe_out && setup_pipe(pipefd))
			return (1);
		if (is_built_in && !cmd->pipe_out)
		{
			handle_redirections(cmd);
			execute_builtin(cmd, env, shell);
			//restore
		}
		else
		{
			pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
				handle_pipe_fds(cmd, pipefd);
				handle_redirections(cmd);
				if (is_built_in)
					execute_builtin(cmd, env, shell);
				else
					execve(cmd_path, cmd->args, env_to_array(env));
			}
			else
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
		}
		cmd = cmd->next;
	}
	wait(&status);
	return (0);
}
