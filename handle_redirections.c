/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:10 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/26 15:31:59 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_fd(char *filename, int flags, int std_fd)
{
	int			fd;
	int			ret;

	if (flags & O_CREAT)
		fd = open(filename, flags, 0644);
	else
		fd = open(filename, flags);
	if (check_fail(fd, filename))
		return (1);
	ret = dup2(fd, std_fd);
	if (check_fail(ret, filename))
		return (1);
	close(fd);
	return (0);
}

static int	redirect_heredoc(int fd, int std_fd)
{
	int	ret;

	ret = dup2(fd, std_fd);
	if (check_fail(ret, "heredoc"))
		return (1);
	close(fd);
	return (0);
}

int	setup_redirections(int type, char *filename)
{
	int	fd;
	int	ret;

	if (type == TOKEN_RD_IN)
	{
		if (redirect_fd(filename, O_RDONLY, STDIN_FILENO))
			return (1);
	}
	else if (type == TOKEN_RD_OUT)
	{
		if (redirect_fd(filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO))
			return (1);
	}
	else if (type == TOKEN_APPEND)
	{
		if (redirect_fd(filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO))
			return (1);
	}
	return (0);
}

// t_fd_backup	*init_fd_backup(t_command *cmd)
// {
	
// }

t_fd_backup	*handle_redirections(t_command *cmd)
{
	t_redirection	*redirect;
	t_fd_backup		*fd_backup;

	fd_backup = malloc(sizeof(t_fd_backup));
	if (!fd_backup)
		return (NULL);
	fd_backup->has_redirection = 0;
	if (!cmd->rds)
		return (fd_backup);
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
	fd_backup->has_redirection = 1;
	redirect = cmd->rds;
	while (redirect)
	{
		if (redirect->type == TOKEN_RD_IN)
		{
			if (setup_redirections(TOKEN_RD_IN, redirect->filename_or_delimiter))
				return (NULL);
		}
		else if (redirect->type == TOKEN_RD_OUT)
		{
			if (setup_redirections(TOKEN_RD_OUT, redirect->filename_or_delimiter))
				return (NULL);
		}
		else if (redirect->type == TOKEN_APPEND)
		{
			if (setup_redirections(TOKEN_APPEND, redirect->filename_or_delimiter))
				return (NULL);
		}
		else if (redirect->type == TOKEN_HEREDOC && redirect->heredoc_fd != -1)
		{
			if (redirect_heredoc(redirect->heredoc_fd, STDIN_FILENO))
				return (NULL);
		}
		redirect = redirect->next;
	}
	return (fd_backup);
}
