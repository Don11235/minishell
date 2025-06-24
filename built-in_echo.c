/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:04:54 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/22 20:19:29 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		flag = 1;
		i++;
	}
	while (args[i] && !ft_strcmp(args[i], "-n"))
		i++;
	while (args[i])
	{
		if (printf("%s", args[i++]) == -1)
			return (1);
		if (args[i] != NULL && printf(" ") == -1)
			return (1);
	}
	if (flag == 0)
	{
		if (printf("\n") == -1)
			return (1);
	}
	return (0);
}
