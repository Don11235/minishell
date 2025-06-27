/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:11:44 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/26 18:46:47 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (print_getcwd_error("pwd"));
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}