/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:26:41 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/14 16:30:11 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s != ch && *s)
		s++;
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

int	check_and_set_builtin(t_cmd *cmd_list)
{
	char	*cmd;

	cmd = cmd_list->argv[0];
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "pwd") 
		|| ft_strcmp(cmd, "export") || ft_strcmp(cmd, "unset") || ft_strcmp(cmd, "env") 
			|| ft_strcmp(cmd, "exit"))
	{
		cmd_list->built_in = 1;
		return (1);
	}
	else
		return (0);
}

int	find_command_in_path(t_cmd *cmd)
{
	int	flag;

	flag = 0;
	if (ft_strchr(cmd->argv[0], '/'))
		if (!access(cmd->argv[0], F_OK))
			flag = 1;
	else
	{
		char	*path;
		char	*cmd_path;
		char	**path_dir;
		int		i;

		i = 0;
		path = getenv("PATH");
		path_dir = ft_split(path, ':');
		if (path_dir == NULL)
			return (-1);
		while (path[i])
		{
			cmd_path = ft_strjoin(path[i], cmd->argv[0]);
			if (cmd_path == NULL)
				return (-1);
			if (!access(cmd_path, F_OK))
			{
				cmd->path = cmd_path;
				flag = 1;
				break ;
			}
			i++;
		}
	}
	return (flag);
}

int	check_cmd(t_cmd *cmd)
{
	if (check_and_set_builtin(cmd))
		return (0);
	else if (find_command_in_path(cmd))
		return (0);
	return (1);
}