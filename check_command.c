/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:26:41 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/01 19:15:58 by ytlidi           ###   ########.fr       */
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

int	check_and_set_builtin(t_command *comd)
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

int	find_command_in_path(t_command *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (!access(cmd->args[0], F_OK))
			return (1);
		else
		{
			printf("minishell: %s: No such file or directory\n", cmd->args[0]);
			return (0);
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
			return (-1);
		path_dir = ft_split(path, ':'); //free
		if (path_dir == NULL)
			return (-1);
		while (path_dir[i])
		{
			cmd_path = ft_strjoin(path_dir[i], cmd->args[0]);
			if (cmd_path == NULL) //free path dir
				return (-1);
			if (!access(cmd_path, F_OK))
				return (1);
			i++;
		}
		printf("minishell: %s: command not found\n", cmd->args[0]);
	}
	return (0);
}

int	check_cmd(t_command *cmd)
{
	if (check_and_set_builtin(cmd))
		return (0);
	else if (find_command_in_path(cmd))
		return (0);
	return (1);
}