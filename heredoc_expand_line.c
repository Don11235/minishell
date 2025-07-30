/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:38:11 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/30 16:44:49 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hdpart	*ft_lstnew_hd(char *str, int expand)
{
	t_hdpart	*new;

	new = (t_hdpart *)malloc(sizeof(t_hdpart));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	new->should_expand = expand;
	new->next = NULL;
	return (new);
}

static t_hdpart	*ft_lstlast(t_hdpart *part)
{
	if (part == NULL)
		return (NULL);
	while (part->next != NULL)
		part = part->next;
	return (part);
}

static void	ft_lstadd_back_hd(t_hdpart **part, t_hdpart *new)
{
	t_hdpart	*last;

	if (part == NULL || new == NULL)
		return ;
	if (*part == NULL)
		*part = new;
	else
	{
		last = ft_lstlast(*part);
		last->next = new;
	}
}

t_hdpart	*split_heredoc_line(char *line)
{
	int			i = 0;
	int			j = 0;
	t_hdpart	*parts = NULL;
	t_hdpart	*new_part;
	char		*substr;
	int			var_len;

	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '?' || line[i + 1] == '$'))
		{
			if (i > j)
			{
				substr = ft_substr(line, j, i - j);
				new_part = ft_lstnew_hd(substr, 0);
				ft_lstadd_back_hd(&parts, new_part);
				free(substr);
			}
			var_len = 1;
			if (line[i + 1] == '?' || line[i + 1] == '$')
				var_len = 2;
			else
			{
				while (ft_isalnum(line[i + var_len]) || line[i + var_len] == '_')
					var_len++;
			}
			substr = ft_substr(line, i, var_len);
			new_part = ft_lstnew_hd(substr, 1);
			ft_lstadd_back_hd(&parts, new_part);
			free(substr);
			i += var_len;
			j = i;
		}
		else
			i++;
	}
	if (i > j)
	{
		substr = ft_substr(line, j, i - j);
		new_part = ft_lstnew_hd(substr, 0);
		ft_lstadd_back_hd(&parts, new_part);
		free(substr);
	}
	return (parts);
}

char	*join_heredoc_parts(t_hdpart *parts)
{
	t_hdpart *current;
	char	*str;
	char	*tmp;

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

char	*heredoc_expand_line(t_env *env, char *line, t_shell *shell)
{
	t_hdpart	*parts;
	char		*key;
	t_env		*env_node;
	t_hdpart	*tmp;
	char		*expanded_line;

	parts = split_heredoc_line(line);
	tmp = parts;
	while (tmp)
	{
		if (tmp->should_expand)
		{
			key = ft_substr(tmp->str, 1, ft_strlen(tmp->str) - 1);
			env_node = find_env(env, key);
			if (env_node)
			{
				free(tmp->str);
				tmp->str = env_node->value;
			}
			else if (key[0] == '$')
			{
				free(tmp->str);
				tmp->str = "$";
				free(key);
			}
			else if (key[0] == '?')
			{
				free(tmp->str);
				tmp->str = ft_itoa(shell->last_exit_status);
				free(key);
			}
			else
			{
				free(tmp->str);
				tmp->str = "";
			}
			free(key);
		}
		tmp = tmp->next;
	}
	expanded_line = join_heredoc_parts(parts);
	return (expanded_line);
}
