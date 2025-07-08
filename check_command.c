/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:26:41 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/08 11:58:15 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	if (s == NULL)
		return (NULL);
	ch = (char)c;
	while (*s != ch && *s)
		s++;
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

int	check_builtin(t_command *comd)
{
	char	*cmd;

	cmd = comd->args[0];
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") 
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") 
			|| !ft_strcmp(cmd, "exit"))
	{
		return (1);
	}
	else
		return (0);
}

char	*resolve_command_path(t_command *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (!access(cmd->args[0], F_OK))
			return (cmd->args[0]);
		else
		{
			print_cmd_error(cmd->args[0], "No such file or directory", 127);
			return (NULL);
		}
	}
	else
	{
		char	*path;
		char	*cmd_path;
		char	**path_dir;
		int		i;

		i = 0;
		path = getenv("PATH");
		if (!path)
			return (NULL);
		path_dir = ft_split(path, ':'); //free
		if (path_dir == NULL)
			return (NULL);
		while (path_dir[i])
		{
			cmd_path = ft_strjoin_with(path_dir[i], cmd->args[0], '/');
			if (cmd_path == NULL) //free path dir
				return (NULL);
			if (!access(cmd_path, F_OK))
				return (cmd_path);
			i++;
		}
		print_cmd_error(cmd->args[0], "command not found", 127);
	}
	return (NULL);
}
