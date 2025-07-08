/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:35:32 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/08 13:10:16 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_command *cmd, t_env *env_list, t_shell *shell)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (cd(cmd->args[1], &env_list, shell));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (pwd(shell));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (export(&env_list, cmd->args, shell));
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (env(env_list, shell));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (unset(&env_list, cmd->args, shell));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (exit_b(cmd->args, shell));
	return (0);
}
