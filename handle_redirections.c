/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:10 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/07 18:53:17 by mben-cha         ###   ########.fr       */
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

static int	setup_redirect(int type, char *filename)
{
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

int	handle_redirections(t_redirection *redirect)
{
	while (redirect)
	{
		if (redirect->type == TOKEN_RD_IN)
		{
			if (setup_redirect(TOKEN_RD_IN, redirect->filename_or_delimiter))
				return (1);
		}
		else if (redirect->type == TOKEN_RD_OUT)
		{
			if (setup_redirect(TOKEN_RD_OUT, redirect->filename_or_delimiter))
				return (1);
		}
		else if (redirect->type == TOKEN_APPEND)
		{
			if (setup_redirect(TOKEN_APPEND, redirect->filename_or_delimiter))
				return (1);
		}
		else if (redirect->type == TOKEN_HEREDOC && redirect->heredoc_fd != -1)
		{
			if (redirect_heredoc(redirect->heredoc_fd, STDIN_FILENO))
				return (1);
		}
		redirect = redirect->next;
	}
	return (0);
}
