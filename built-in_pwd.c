/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:11:44 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/28 18:39:30 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_shell *shell)
{
	char	*pwd;
	int		ret;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ret = print_getcwd_error("pwd");
		return (shell->last_exit_status = ret, ret);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (shell->last_exit_status = 0, 0);
}