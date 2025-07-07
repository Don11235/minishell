/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:46:50 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/07 18:18:19 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(t_token *token, t_env *env)
{
	char	*str;
	char	*new_str;
	char	q;
	t_env	*env_line;

	int (i), (j), (continue_flag), flag = 0;
	j = 0;
	str = remove_quote_func_init(&i, token, &new_str, env);
	while (str[i] != '\0')
	{
		continue_flag = skipping_if_quote_mark(str, &i, &flag, &q);
		if (expand_condition(str, i, flag, q) && token->type != TOKEN_HEREDOC)
		{
			continue_flag = printing_dollar(new_str, &j, str, &i);
			env_line = find_env_exp(env, &str[i]);
			continue_flag = expand_to_an_empty_string(str, &i, env_line);
			continue_flag = expand_to_a_real_value(new_str, &j, &i, env_line);
		}
		if (continue_flag == 1)
			continue ;
		new_str[j++] = str[i++];
	}
	if (in_case_of_quote_not_closed(new_str, j, flag))
		return (free(str), NULL);
	return (free(str), new_str);
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
	t_redirection **redirection_list, t_env *env)
{
	t_redirection	*redirection;
	char			**args;
	int				i;

	i = 0;
	args = malloc(sizeof(char *) * (words_count(*current_token) + 1)); //free
	while (*current_token != NULL && (*current_token)->type != TOKEN_PIPE)
	{
		if (*current_token != NULL && (*current_token)->type < 3)
		{
			args[i] = remove_quote(*current_token, env); //free
			if (args[i++] == NULL) //free function
				return (NULL);
			*current_token = (*current_token)->next;
		}
		else if ((*current_token)->type >= 4 && (*current_token)->type <= 7)
		{
			redirection = ft_lstnew_redirection((*current_token)->type,
				remove_quote(*current_token, env)); //free
			ft_lstadd_back_redirection(&redirection_list, redirection);
			*current_token = (*current_token)->next->next;
		}
	}
	args[i] = NULL;
	return (args);
}

t_command	*filling_cmd_list(t_token *token_list, int pipe_flag, t_env *env)
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
		args = inner_filling_cmd_list(&current_token, &redirection_list, env);
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

t_command	*parse_input(char *str, t_env *env)
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
	if (valid_tokens(token_list))
		return (NULL);
	command_list = filling_cmd_list(token_list, 0, env);
	return (command_list);
}
