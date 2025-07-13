/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:06:27 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/09 12:44:08 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory(char *path, t_env **env)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (print_getcwd_error("cd"));
	if (chdir(path) == -1)
	{
		print_chdir_error(path);
		free(old_pwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (print_getcwd_error("cd"));
	if (update_env(*env, "PWD", pwd))
		return (free(old_pwd), free(pwd), 1);
	free(pwd);
	if (update_env(*env, "OLDPWD", old_pwd))
		return (free(old_pwd), 1);
	free(old_pwd);
	return (0);
}

int	cd(char *path, t_env **env, t_shell *shell)
{
	t_env	*home;
	int		result;

	if (!path)
	{
		home = find_env(*env, "HOME");
		if (!home)
			return (shell->last_exit_status = 1, 1);
		result = change_directory(home->value, env);
	}
	else
		result = change_directory(path, env);
	return (shell->last_exit_status = result, result);
}
