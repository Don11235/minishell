/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:58:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/30 18:10:21 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe_fds(t_command *cmd, int *pipefd)
{
	int	ret1;
	int	ret2;

	if (cmd->pipe_out)
	{
		ret1 = dup2(pipefd[1], STDOUT_FILENO);
		check_or_exit(ret1, "dup2");
		close(pipefd[1]);
	}
	else
		close(pipefd[1]);
	if (cmd->pipe_in)
	{
		ret2 = dup2(pipefd[0], STDIN_FILENO);
		check_or_exit(ret2, "dup2");
		close(pipefd[0]);
	}
	else
		close(pipefd[0]);
}

void	handle_redirections(t_command *cmd)
{
	if (!cmd->rds)
		return ;
	t_redirection	*redirect;

	redirect = cmd->rds;
	while (redirect)
	{
		if (redirect->type == TOKEN_RD_IN)
			setup_redirections(TOKEN_RD_IN, redirect->filename_or_delimiter);
		else if (redirect->type == TOKEN_RD_OUT)
			setup_redirections(TOKEN_RD_OUT, redirect->filename_or_delimiter);
		else if (redirect->type == TOKEN_APPEND)
			setup_redirections(TOKEN_APPEND, redirect->filename_or_delimiter);
	}
}

int	execute(t_command *cmd_list, char **envp)
{
	t_command	*cmd;
	pid_t		pid;
	int			pipefd[2];

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->pipe_out && setup_pipe(pipefd))
			return (1);
		if (cmd->built_in && !cmd->pipe_out)
			execute_builtin(cmd);
		else
		{
			pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
				handle_pipe_fds(cmd, pipefd);
				handle_redirections(cmd);
				if (cmd->built_in)
					execute_builtin(cmd);
				else
					execve(cmd->path, cmd->args, envp);
			}
		}
		cmd = cmd->next;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
