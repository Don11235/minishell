/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_line_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:19:59 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 16:50:16 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_plain_text_part(t_hdpart **parts, char *line, int i, int j)
{
	t_hdpart	*new_part;
	char		*substr;

	if (i > j)
	{
		substr = ft_substr(line, j, i - j);
		new_part = ft_lstnew_hd(substr, 0);
		ft_lstadd_back_hd(parts, new_part);
		free(substr);
	}
}

void	add_dollar_variable(t_hdpart **parts, char *line, int i, int var_len)
{
	t_hdpart	*new_part;
	char		*substr;

	substr = ft_substr(line, i, var_len);
	new_part = ft_lstnew_hd(substr, 1);
	ft_lstadd_back_hd(parts, new_part);
	free(substr);
}

int	get_var_len(char *line, int i)
{
	int	var_len;

	var_len = 1;
	if (line[i + 1] == '?' || line[i + 1] == '$')
		var_len = 2;
	else
	{
		while (ft_isalnum(line[i + var_len]) || line[i + var_len] == '_')
			var_len++;
	}
	return (var_len);
}
