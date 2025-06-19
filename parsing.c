/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:46:50 by ytlidi            #+#    #+#             */
/*   Updated: 2025/06/18 18:32:36 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filling_pipes(t_command *command, t_token *current_token)
{
	int	pipe;
	
	if (pipe == 1)
		command->pipe_in = 1;
	if (current_token != NULL && current_token->type == TOKEN_PIPE)
	{
		command->pipe_out = 1;
		pipe = 1;
		current_token = current_token->next;
	}	
}

t_command	*filling_cmd_list(t_token *token_list)
{
	t_token			*current_token;
	t_command		*command_list;
	t_command		*command;
	t_redirection	*redirection_list;
	t_redirection	*redirection;
	char			**args;
	int				i;

	command_list = NULL;
	current_token = token_list;
	i = 0;
	while (current_token != NULL)
	{
		command = NULL;
		redirection_list = NULL;
		while (current_token != NULL && current_token->type != TOKEN_PIPE)
		{
			args = malloc(sizeof(char *) * (words_count(token_list) + 1)); //free
			if (current_token != NULL && current_token->type < 3)
			{
				args[i] = remove_quote(current_token->token); //free
				current_token = current_token->next;
				i++;
			}
			else if (current_token->type >= 4 && current_token->type <= 7)
			{
				redirection = ft_lstnew_redirection(current_token->type, current_token->next->token); //free
				ft_lstadd_back_redirection(&redirection_list, redirection);
				current_token = current_token->next->next;
			}
		}
		command = ft_lstnew_command(args); //free
		command->rds = redirection_list;
		filling_pipes(&command, current_token);
		ft_lstadd_back_command(&command_list, command);		
	}
}

t_command	*parse_input(char *str)
{
	t_token		*token_list;
	t_command	*command_list;
	int			i;

	token_list = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (quote_tokens(str, &token_list, &i))
			return (NULL);
		if (pipes_and_rds_tokens(str, &token_list, &i))
			return (NULL);
		if (word_tokens(str, &token_list, &i))
			return (NULL);
	}
	command_list = NULL;
}