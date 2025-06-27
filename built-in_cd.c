/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:06:27 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/27 19:53:10 by mben-cha         ###   ########.fr       */
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
	if (!find_env(*env, "OLDPWD"))
		add_env(env, "OLDPWD", old_pwd);
	else if (update_env(*env, "OLDPWD", old_pwd))
		return (free(old_pwd), 1);
	free(old_pwd);
	return (0);
}

int	cd(char *path, t_env **env)
{
	t_env	*home;
	t_env	*old_pwd;
	
	home = find_env(*env, "HOME");
	old_pwd = find_env(*env, "OLDPWD");
	if (!home || !old_pwd)
		return (1);
	if (!path || !ft_strcmp(path, "~"))
		return (change_directory(home->value, env));
	if (path && !ft_strcmp(path, "-"))
		return (change_directory(old_pwd->value, env));
	return (change_directory(path, env));
}
