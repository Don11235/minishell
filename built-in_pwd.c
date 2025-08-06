/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:11:44 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/06 06:33:04 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_shell *shell, t_env *env)
{
	char	*pwd;
	t_env	*env_node;
	int		ret;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		env_node = find_env(env, "PWD");
		if (!env_node)
		{
			ret = print_getcwd_error("pwd");
			return (shell->last_exit_status = ret, ret);
		}
		else
			pwd = ft_strdup(env_node->value);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (shell->last_exit_status = 0, 0);
}
