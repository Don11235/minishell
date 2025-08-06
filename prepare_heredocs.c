/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 03:52:19 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/05 23:58:28 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(t_redirection *redirect, int *pipefd, t_env **env,
	t_shell *shell)
{
	char	*line;
	char	*final_line;

	set_signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redirect->filename_or_delimiter))
		{
			free(line);
			exit(0);
		}
		if (redirect->is_delimiter_unquoted)
		{
			final_line = heredoc_expand_line(env, line, shell);
			ft_putstr_fd(final_line, pipefd[1]);
			free(final_line);
		}
		else
			ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	exit(0);
}

int	wait_heredoc(pid_t pid, int *pipefd, t_command *cmd_list, t_shell *shell)
{
	int	status;

	set_signal(SIGINT, SIG_IGN);
	close(pipefd[1]);
	if (waitpid(pid, &status, 0) == -1)
		return (check_fail(-1, "waitpid"));
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		write(1, "\n", 1);
		reset_all_heredoc_fds(cmd_list);
		shell->last_exit_status = 1;
		return (1);
	}
	return (0);
}

static int	do_pipe_and_fork(int pipefd[2], pid_t *pid)
{
	if (setup_pipe(pipefd))
		return (1);
	*pid = fork();
	if (*pid == -1)
		return (1);
	return (0);
}

static int	process_heredocs(t_command *cmd, t_command *cmd_list, t_env **env,
	t_shell *shell)
{
	t_redirection	*redirect;
	pid_t			pid;
	int				pipefd[2];

	redirect = cmd->rds;
	while (redirect)
	{
		if (redirect->type == TOKEN_HEREDOC)
		{
			if (do_pipe_and_fork(pipefd, &pid))
				return (1);
			if (pid == 0)
				read_heredoc(redirect, pipefd, env, shell);
			else
			{
				if (wait_heredoc(pid, pipefd, cmd_list, shell))
					return (1);
				redirect->heredoc_fd = pipefd[0];
			}
		}
		redirect = redirect->next;
	}
	return (0);
}

int	prepare_heredocs(t_command *cmd, t_env **env, t_shell *shell)
{
	t_redirection	*redirect;
	t_command		*cmd_list;

	cmd_list = cmd;
	while (cmd)
	{
		redirect = cmd->rds;
		if (process_heredocs(cmd, cmd_list, env, shell))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
