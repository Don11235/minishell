/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:10 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/20 21:55:42 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_fd(char *filename, int flags, int std_fd)
{
	int	fd;
	int	ret;

	if (flags & O_CREAT)
		fd = open(filename, flags, 0644);
	else
		fd = open(filename, flags);
	check_or_exit(fd, "open");
	ret = dup2(fd, std_fd);
	check_or_exit(ret, "dup2");
	close(fd);
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
