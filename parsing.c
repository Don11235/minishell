/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:46:50 by ytlidi            #+#    #+#             */
/*   Updated: 2025/08/01 16:42:37 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filling_pipes(t_command *command, t_token *current_token)
{
	int	pipe;

	pipe = 0;
	while (current_token != NULL)
	{
		if (pipe == 1)
			command->pipe_in = 1;
		if (current_token != NULL && current_token->type == TOKEN_PIPE)
		{
			command->pipe_out = 1;
			pipe = 1;
			break ;
		}
		current_token = current_token->next;
	}
}

int	in_case_of_type_greater_than_3(t_token **current_token,
	t_redirection **redirection_list, t_env *env, t_shell *shell)
{
	t_redirection	*redirection;
	t_arg_word		*quote_removed;

	quote_removed = remove_quote(*current_token, env, shell);
	if (quote_removed == NULL)
		return (-1);
	redirection = ft_lstnew_redirection((*current_token)->type,
			quote_removed->str);
	if ((*current_token)->type == TOKEN_HEREDOC)
		redirection->is_delimiter_unquoted = is_unquoted
			((*current_token)->next->token);
	ft_lstadd_back_redirection(&redirection_list, redirection);
	return (free(quote_removed->str), free(quote_removed), 0);
}

char	**inner_filling_cmd_list(t_token **current_token,
	t_redirection **redirection_list, t_env *env, t_shell *shell)
{
	char	**args;
	t_token	*list;
	int		count;

	list = NULL;
	count = args_count(*current_token, env, shell, &list);
	if (count == -1)
		return (free_list(list), NULL);
	args = malloc(sizeof(char *) * (count + 1));
	list_to_args(list, args);
	free_list(list);
	while (*current_token != NULL && (*current_token)->type != TOKEN_PIPE)
	{
		if (*current_token != NULL && (*current_token)->type < 3)
			*current_token = (*current_token)->next;
		else if ((*current_token)->type >= 4 && (*current_token)->type <= 7)
		{
			if (in_case_of_type_greater_than_3(current_token, redirection_list, 
					env, shell) == -1)
				return (NULL);
			*current_token = (*current_token)->next->next;
		}
	}
	return (args);
}

t_command	*filling_cmd_list(t_token *token_list, int pipe_flag, t_env *env,
	t_shell *shell)
{
	t_token			*current_token;
	t_command		*command_list;
	t_command		*command;
	t_redirection	*rd_list;
	char			**args;

	command_list = NULL;
	current_token = token_list;
	while (current_token != NULL)
	{
		rd_list = NULL;
		args = inner_filling_cmd_list(&current_token, &rd_list, env, shell);
		if (args == NULL)
			return (NULL);
		command = ft_lstnew_command(args);
		if (pipe_flag == 1)
			command->pipe_in = 1;
		pipe_flag = 1;
		command->rds = rd_list;
		filling_pipes(command, current_token);
		ft_lstadd_back_command(&command_list, command);
		if (current_token != NULL)
			current_token = current_token->next;
	}
	return (command_list);
}

t_command	*parse_input(char *str, t_env *env, t_shell *shell)
{
	t_token		*token_list;
	t_command	*command_list;
	int			i;

	token_list = NULL;
	command_list = NULL;
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
	if (valid_tokens(token_list, shell))
		return (free_list(token_list), NULL);
	command_list = filling_cmd_list(token_list, 0, env, shell);
	free_list(token_list);
	return (command_list);
}
