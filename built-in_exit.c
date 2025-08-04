/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:42:50 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 18:11:11 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_exit_valid(char *arg)
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

static void	get_sign(const char **str, long int *sign)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

static long	ft_atol(const char *str)
{
	long int	num;
	long int	sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	get_sign(&str, &sign);
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

int	do_exit(t_command *cmd, t_shell *shell)
{
	long int	exit_code;

	if (cmd->pipe_in || cmd->pipe_out)
		return (0);
	write(1, "exit\n", 6);
	if (!cmd->args[1])
		exit (shell->last_exit_status);
	if (is_exit_valid(cmd->args[1]))
		exit(255);
	if (cmd->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->last_exit_status = 1;
		return (1);
	}
	exit_code = ft_atol(cmd->args[1]);
	if (exit_code == -1)
	{
		print_exit_error(cmd->args[1]);
		exit(255);
	}
	exit(exit_code);
}
