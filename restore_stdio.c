/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_stdio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:31:23 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/03 15:30:56 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restore_stdio(int saved_stdin, int saved_stdout)
{
	int	ret;

	ret = dup2(saved_stdin, STDIN_FILENO);
	if (check_fail(ret, "dup2"))
		return (1);
	close(saved_stdin);
	ret = dup2(saved_stdout, STDOUT_FILENO);
	if (check_fail(ret, "dup2"))
		return (1);
	close(saved_stdout);
	return (0);
}
