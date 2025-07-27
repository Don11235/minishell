/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:46:11 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/27 16:58:21 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

static void	free_redirecrion(t_redirection *rd)
{
	t_redirection	*tmp;

	while (rd)
	{
		free(rd->filename_or_delimiter);
		tmp = rd;
		rd = rd->next;
		free(tmp);
	}
}

void	free_cmd_list(t_command *cmd_list)
{
	t_command	*tmp;

	while (cmd_list)
	{
		free_args(cmd_list->args);
		free_redirecrion(cmd_list->rds);
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free(tmp);
	}
}