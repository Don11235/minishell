/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:00:31 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/06 18:28:03 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_equal_sign(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	add_key_value(t_env **env, char *arg)
{
	char	**key_value;
	t_env	*exist;

	key_value = ft_split(arg, '=');
	if (!key_value)
		return (1);
	exist = find_env(*env, key_value[0]);
	if (!key_value[1])
	{
		if (!exist)
			add_env(env, key_value[0], "");
		else
			update_env(*env, key_value[0], "");
	}
	else
	{
		if (!exist)
			add_env(env, key_value[0], key_value[1]);
		else
			update_env(*env, key_value[0], key_value[1]);
	}
	free_split(key_value);
	return (0);
}

void	print_export_env(t_env *env)
{
	t_env	**sorted_array;
	int		i;

	i = 0;
	sorted_array = get_sorted_env_ptr_array(env);
	while (sorted_array[i])
	{
		if (!sorted_array[i]->value)
			printf("declare -x %s\n", sorted_array[i]->key);
		else
			printf("declare -x %s=\"%s\"\n", sorted_array[i]->key,
				sorted_array[i]->value);
		i++;
	}
	free(sorted_array);
}

void	add_or_update_export(t_env **env, char *key)
{
	if (!find_env(*env, key))
		add_env(env, key, NULL);
	else
		update_env(*env, key, NULL);
}

int	export(t_env **env, char **args, t_shell *shell)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!args[1])
		print_export_env(*env);
	while (args[i])
	{
		if (is_export_valid(args[i]))
		{
			status = 1;
			i++;
			continue ;
		}
		if (has_equal_sign(args[i]))
		{
			if (add_key_value(env, args[i]))
				return (shell->last_exit_status = 1, 1);
		}
		else
			add_or_update_export(env, args[i]);
		i++;
	}
	return (shell->last_exit_status = status, status);
}
