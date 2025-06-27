/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:49:48 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/27 21:06:18 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) || arg[0])
		return (print_export_error(arg));
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (print_export_error(arg));
	}
	return (0);
}

int	unset(char *key)
{
	
}
