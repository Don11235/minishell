/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:22:07 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/12 20:58:02 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_numeric(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '+' || value[i] == '-')
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_shlvl(char *value)
{
	char	*shlvl;
	int		lvl;

	if (!is_valid_numeric(value))
		return 1;
	lvl = ft_atoi(value);
	if (lvl < 0)
		return 0;
	if (lvl > 1000)
	{
		shlvl = ft_itoa(lvl + 1);
		if (!shlvl)
			return (1);
		print_shlvl_too_high_error(shlvl);
		free(shlvl);
		return (1);
	}
	return lvl + 1;
}


static void	update_shlvl(t_env *env_list)
{
	t_env	*shlvl_node;
	char	*shlvl_value;
	int		shlvl_number;

	shlvl_node = find_env(env_list, "SHLVL");
	if (shlvl_node)
	{
		shlvl_value = shlvl_node->value;
		shlvl_number = parse_shlvl(shlvl_value);
		shlvl_value = ft_itoa(shlvl_number);
		shlvl_node->value = shlvl_value;
	}
	else
		add_env(&env_list, "SHLVL", "1");
}

t_env	*init_env(char **envp)
{
	int		i;
	char	**key_value;
	t_env	*new;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		if (key_value == NULL)
			return (NULL);
		new = ft_lstnew(key_value[0], key_value[1]);
		ft_lstadd_back(&env_list, new);
		free_split(key_value);
		i++;
	}
	if (!find_env(env_list, "OLDPWD"))
		add_env(&env_list, "OLDPWD", NULL);
	update_shlvl(env_list);
	return (env_list);
}
