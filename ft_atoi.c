/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:42:58 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/12 20:45:01 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	long long int	num;
	int				sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (num > (9223372036854775807LL - (*str - '0')) / 10)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)(num * sign));
}
