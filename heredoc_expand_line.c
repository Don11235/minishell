/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:38:11 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/06 00:00:45 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hdpart	*split_heredoc_line(char *line)
{
	int			i;
	int			j;
	t_hdpart	*parts;
	int			var_len;

	i = 0;
	j = 0;
	parts = NULL;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '?'
				|| line[i + 1] == '$'))
		{
			add_plain_text_part(&parts, line, i, j);
			var_len = get_var_len(line, i);
			add_dollar_variable(&parts, line, i, var_len);
			i += var_len;
			j = i;
		}
		else
			i++;
	}
	add_plain_text_part(&parts, line, i, j);
	return (parts);
}

char	*join_heredoc_parts(t_hdpart *parts)
{
	t_hdpart	*current;
	char		*str;
	char		*tmp;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	current = parts;
	while (current)
	{
		tmp = ft_strjoin(str, current->str);
		free(str);
		str = tmp;
		current = current->next;
	}
	return (str);
}

void	replace_hd_variable(t_hdpart *tmp, t_env *env_node, t_shell *shell,
	char *key)
{
	if (env_node)
	{
		free(tmp->str);
		tmp->str = ft_strdup(env_node->value);
	}
	else if (key[0] == '$')
	{
		free(tmp->str);
		tmp->str = ft_strdup("$");
		free(key);
	}
	else if (key[0] == '?')
	{
		free(tmp->str);
		tmp->str = ft_strdup(ft_itoa(shell->last_exit_status));
		free(key);
	}
	else
	{
		free(tmp->str);
		tmp->str = ft_strdup("");
		free(key);
	}
}

void	expand_hd_variable(t_hdpart	*tmp, t_env **env, t_shell *shell)
{
	char	*key;
	t_env	*env_node;

	key = ft_substr(tmp->str, 1, ft_strlen(tmp->str) - 1);
	env_node = find_env(*env, key);
	replace_hd_variable(tmp, env_node, shell, key);
}

char	*heredoc_expand_line(t_env **env, char *line, t_shell *shell)
{
	t_hdpart	*parts;
	t_hdpart	*tmp;
	char		*expanded_line;

	parts = split_heredoc_line(line);
	tmp = parts;
	while (tmp)
	{
		if (tmp->should_expand)
			expand_hd_variable(tmp, env, shell);
		tmp = tmp->next;
	}
	expanded_line = join_heredoc_parts(parts);
	return (free_hd_parts(parts), expanded_line);
}
