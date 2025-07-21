/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:58:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/21 18:11:09 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_fds(t_command *cmd, int prev_read_end, int *pipefd)
{
	int	ret;

	if (cmd->pipe_in && prev_read_end != -1)
	{
		ret = dup2(prev_read_end, STDIN_FILENO);
		if (check_fail(ret, "pipe read"))
			return (1); 
		close(prev_read_end);
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
					if (!redirect->is_delimiter_quoted)
						// line = 
					if (!line || !ft_strcmp(line, redirect->filename_or_delimiter))
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
	int			prev_read_end = -1;


	cmd = cmd_list;
	prepare_heredocs(cmd);
	while (cmd)
	{
		is_built_in = check_builtin(cmd);
		if (!is_built_in)
			cmd_path = resolve_command_path(cmd, env);
		if (!cmd_path)
			return (1);
		if (cmd->pipe_out && setup_pipe(pipefd))
			return (1);
		if (is_built_in && !cmd->pipe_in && !cmd->pipe_out)
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
			else
				free(fd_backup);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
				set_signal(SIGINT, SIG_DFL);
				set_signal(SIGQUIT, SIG_DFL);
				if (handle_pipe_fds(cmd, prev_read_end, pipefd))
					exit(1);
				fd_backup = handle_redirections(cmd);
				if (!fd_backup)
					exit(1);
				if (is_built_in)
					execute_builtin(cmd, env, shell);
				else
					execve(cmd_path, cmd->args, env_to_array(env));
				exit(0);
			}
			else
			{	
				set_signal(SIGINT, SIG_IGN);
				if (prev_read_end != -1)
					close(prev_read_end);
				if (cmd->pipe_out)
				{
					close(pipefd[1]);
					prev_read_end = pipefd[0];
				}
				else
					prev_read_end = -1;
			}
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0);
	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		else if (sig == SIGINT)
			write(1, "\n", 1);
	}
	return (0);
}
