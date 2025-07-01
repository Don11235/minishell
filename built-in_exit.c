/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:42:50 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/28 23:21:34 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *arg)
{
	int	i;
	
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) || i > 18)
			return (print_exit_error(arg), 1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long int	num;
	long int	sign;

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
		if (num < (LONG_MIN + (*str - '0')) / 10)
			return (-1);
		num = num * 10 - (*str - '0');
		str++;
	}
	if (sign == 1)
	{
		if (num == LONG_MIN)
			return (-1);
		return (-num);
	}
	return (num);
}

void	exit_b(char **args, t_shell *shell)
{
	long int	exit_code;

	write(1, "exit\n", 5);
	if (!args[1])
		exit (shell->last_exit_status);
	if (is_valid(args[1]))
		exit(255);
	if (args[2])
	{
		write(2, "minishell: exit: too many arguments", 35);
		shell->last_exit_status = 1;
		return ;
	}
	exit_code = ft_atol(args[1]);
	if (exit_code == -1)
	{
		print_exit_error(args[1]);
		exit(255);
	}
	exit(exit_code);
}
