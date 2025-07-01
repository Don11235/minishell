/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:15:54 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/28 19:15:15 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_getcwd_error(char *cmd_name)
{
	write(2, "minishell: ", 11);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": error retrieving current directory: ", 38);
    write(2, strerror(errno), ft_strlen(strerror(errno)));
    write(2, "\n", 1);
	return (1);
}
int print_chdir_error(char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
    write(2, "\n", 1);
	return (1);
}
int	print_export_error(char *identifier)
{
	write(2, "minishell: export: `", 20);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

void	print_exit_error(char *arg)
{
	write(2, "minishell: export: ", 19);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required", 27);
}
