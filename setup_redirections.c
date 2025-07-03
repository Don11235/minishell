/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:10 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/03 15:24:13 by mben-cha         ###   ########.fr       */
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
	if (check_fail(fd, "open"))
		return (1);
	ret = dup2(fd, std_fd);
	if (check_fail(ret, "dup2"))
		return (1);
	close(fd);
	return (0);
}

static int	redirect_heredoc(char *delimiter)
{
	int	pipefd[2];
	int	ret;

	if (setup_pipe(pipefd))
		return (1);
	close(pipefd[1]);
	ret = dup2(pipefd[0], STDIN_FILENO);
	if (check_fail(ret, "dup2"))
		return (1);
	return (0);
}

void	setup_redirections(int type, char *filename)
{
	int	fd;
	int	ret;

	if (type == TOKEN_RD_IN)
		redirect_fd(filename, O_RDONLY, STDIN_FILENO);
	else if (type == TOKEN_RD_OUT)
		redirect_fd(filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
	else if (type == TOKEN_APPEND)
		redirect_fd(filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}
