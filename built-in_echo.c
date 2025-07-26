/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:04:54 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/26 13:14:25 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	if (arg[i] == '-' && arg[i + 1] == '\0')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;	
	}
	return (1);
}

int	echo(char **args, t_shell *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (args[i] && is_n_option(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i] && is_n_option(args[i]))
		i++;
	while (args[i])
	{
		if (printf("%s", args[i++]) == -1)
			return (shell->last_exit_status = 1, 1);
		if (args[i] != NULL && printf(" ") == -1)
			return (shell->last_exit_status = 1, 1);
	}
	if (flag == 0)
	{
		if (printf("\n") == -1)
			return (shell->last_exit_status = 1, 1);
	}
	
	return (shell->last_exit_status = 0, 0);
}
