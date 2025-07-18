/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:46:50 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/18 19:28:58 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(t_token *token, t_env *env, t_shell *shell)
{
	char		q;
	int			continue_flag;
	t_env		*env_line;
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing)); //free
	if (parsing == NULL)
		return (NULL);
	remove_quote_func_init(parsing, token, env);
	while (parsing->str[parsing->i] != '\0')
	{
		continue_flag = remove_quote_inner_loop(token, env, shell, parsing);
		if (continue_flag == 1)
			continue ;
		parsing->new_str[parsing->j++] = parsing->str[parsing->i++];
	}
	parsing->new_str[parsing->j] = '\0';
	if (in_case_of_quote_not_closed(parsing->new_str, parsing->j, parsing->flag))
		return (free(parsing->str), NULL);
	return (free(parsing->str), parsing->new_str);
}

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

char **inner_filling_cmd_list(t_token **current_token,
	t_redirection **redirection_list, t_env *env, t_shell *shell)
{
	t_redirection	*redirection;
	char			**args;
	int				i;
	char			*file;

	i = 0;
	args = malloc(sizeof(char *) * (words_count(*current_token) + 1)); //free
	while (*current_token != NULL && (*current_token)->type != TOKEN_PIPE)
	{
		if (*current_token != NULL && (*current_token)->type < 3)
		{
			args[i] = remove_quote(*current_token, env, shell); //free
			if (args[i++] == NULL) //free function
				return (NULL);
			*current_token = (*current_token)->next;
		}
		else if ((*current_token)->type >= 4 && (*current_token)->type <= 7)
		{
			file = remove_quote(*current_token, env, shell);
			if (file == NULL)
				return (NULL);
			redirection = ft_lstnew_redirection((*current_token)->type, file);
			if ((*current_token)->type == TOKEN_HEREDOC)
				redirection->is_delimiter_quoted = is_quoted((*current_token)->next->token);
			ft_lstadd_back_redirection(&redirection_list, redirection);
			*current_token = (*current_token)->next->next;
		}
	}
	args[i] = NULL;
	return (args);
}

t_command	*filling_cmd_list(t_token *token_list, int pipe_flag, t_env *env, t_shell *shell)
{
	t_token			*current_token;
	t_command		*command_list;
	t_command		*command;
	t_redirection	*redirection_list;
	char			**args;

	command_list = NULL;
	current_token = token_list;
	while (current_token != NULL)
	{
		redirection_list = NULL;
		args = inner_filling_cmd_list(&current_token, &redirection_list, env, shell);
		if (args == NULL)
			return (NULL);
		command = ft_lstnew_command(args); //free
		if (pipe_flag == 1)
			command->pipe_in = 1;
		pipe_flag = 1;
		command->rds = redirection_list;
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
		return (NULL);
	command_list = filling_cmd_list(token_list, 0, env, shell);
	return (command_list);
}
