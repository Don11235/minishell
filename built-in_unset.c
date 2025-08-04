/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:49:48 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 21:00:01 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_unset_valid(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) || !arg[0])
		return (print_unset_error(arg));
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (print_unset_error(arg));
		i++;
	}
	return (0);
}

static t_env	*find_prev_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	if (!key)
		return (NULL);
	if (!strcmp(key, tmp->key))
		return (tmp);
	while (tmp)
	{
		if (tmp->next && !strcmp(key, tmp->next->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	free_env_node(t_env *env_node)
{
	if (!env_node)
		return ;
	free(env_node->key);
	free(env_node->value);
	free(env_node);
}

static void	unset_env_key(t_env **env, char *key)
{
	t_env	*prev_env;
	t_env	*node_to_remove;

	prev_env = find_prev_env(*env, key);
	if (!prev_env)
		return ;
	else
	{
		if (prev_env == *env)
		{
			*env = prev_env->next;
			free_env_node(prev_env);
		}
		else
		{
			node_to_remove = prev_env->next;
			prev_env->next = node_to_remove->next;
			free_env_node(node_to_remove);
		}
	}
}

int	unset(t_env **env, char **args, t_shell *shell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (is_unset_valid(args[i]))
			status = 1;
		else
			unset_env_key(env, args[i]);
		i++;
	}
	return (shell->last_exit_status = status, status);
}
