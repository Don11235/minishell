/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:46:50 by ytlidi            #+#    #+#             */
/*   Updated: 2025/06/29 22:16:27 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void filling_type_s_or_d_quote(t_token *list)
{
	if (list->token[0] == '\'')
		list->type = TOKEN_S_QUOTE;
	if (list->token[0] == '"')
		list->type = TOKEN_D_QUOTE;
}

int quote_tokens(char *str, t_token **list, int *i)
{
	char	q;
	int		j;
	char	*s;
	t_token	*token;

	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '"')
	{
		q = str[*i];
		j = (*i)++;
		while (str[*i] != q && str[*i] != '\0')
			(*i)++;
		//if (str[*i] == '\0')
		//	printf("quote not closed\n");
		if (*i > j)
		{
			s = ft_substr(str, j, *i - j + 1); //free
			if (s == NULL)
				return (1);
			token = ft_lstnew_token(s); //free
			filling_type_s_or_d_quote(token);
			ft_lstadd_back_token(list, token);
		}
		(*i)++;
	}
	return (0);
}
void filling_type_pipe_or_rd(t_token *list)
{
	if (list->token[1] == '\0')
	{
		if (list->token[0] == '|')
			list->type = TOKEN_PIPE;
		if (list->token[0] == '>')
			list->type = TOKEN_RD_OUT;
		if (list->token[0] == '<')
			list->type = TOKEN_RD_IN;
	}
	else
	{
		if (list->token[1] == '>')
			list->type = TOKEN_APPEND;
		if (list->token[1] == '<')
			list->type = TOKEN_HEREDOC;
	}
}

int inner_pipes_and_rds_tokens(char *str, t_token **list, int **i, int s_or_d)
{
	char 	*s;
	int		j;
	t_token	*token;

	s = malloc(s_or_d + 1); //free
	if (s == NULL)
		return (1);
	j = 0;
	while (j < s_or_d)
	{
		s[j] = str[**i];
		j++;
	}
	s[j] = '\0';
	token = ft_lstnew_token(s); //free
	filling_type_pipe_or_rd(token);
	ft_lstadd_back_token(list, token);
	**i += s_or_d;
	return (0);
}

int pipes_and_rds_tokens(char *str, t_token **list, int *i)
{
	char	rd;

	if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
	{
		rd = str[*i];
		if (str[*i + 1] == rd && rd != '|')
			return (inner_pipes_and_rds_tokens(str, list, &i, 2));
		else
			return (inner_pipes_and_rds_tokens(str, list, &i, 1));
	}
	return (0);
}

int word_tokens(char *str, t_token **list, int *i)
{
	int		j;
	char	*s;
	t_token *token;
	   	
	j = *i;
	while (str[*i] != ' ' && !(str[*i] >= 9 && str[*i] <= 13) && str[*i] != '|'
		&& str[*i] != '>' && str[*i] != '<' && str[*i] != '"' && str[*i] != '\''
		&& str[*i] != '\0')
		(*i)++;
	while ((str[*i] == '"' || str[*i] == '\'') && str[*i] != '\0')
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] != '"' && str[*i] != '\'' && str[*i] != '\0')
				(*i)++;
		}
		(*i)++;
	}
	if (*i > j)
	{
		s = ft_substr(str, j, *i - j + 1); //free
		if (s == NULL)
			return (1);
		(*i)++;
		token = ft_lstnew_token(s); //free
		token->type = TOKEN_WORD; //not necessary (it's 0 by default)
		ft_lstadd_back_token(list, token);
	}
	return (0);
}

int words_count(t_token *beginning)
{
	int		i;
	t_token	*current;

	current = beginning;
	i = 0;
	while (current != NULL && current->type != TOKEN_PIPE)
	{
		if (current->type >= 4 && current->type <= 7)
			current = current->next->next;
		else
			current = current->next;
		i++;
	}
	return i;
}

// void display_redirection_list(t_redirection *head) {
//     t_redirection *current = head;
//     while (current != NULL) {
//         printf("%s(%d) -> ", current->file, current->type);
//         current = current->next;
//     }
//     printf("NULL\n");
// }

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*new_str;
	char	quote;

	i = 0;
	j = 0;
	flag = 0;
	new_str = malloc(ft_strlen(str) + 1);
	while (str[i] != '\0')
	{
		if ((flag % 2 == 0 && (str[i] == '\'' || str[i] == '"'))
			|| (flag % 2 == 1 && str[i] == quote))
		{
			quote = str[i];
			flag++;
			i++;
			continue;
		}
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	if (flag % 2 == 1)
	{
		printf("quote not closed\n");
		return (free(new_str), NULL);
	}
	return (new_str);
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

char **inner_filling_cmd_list(t_token **current_token, t_redirection **redirection_list)
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
			args[i] = remove_quote((*current_token)->token); //free
			if (args[i] == NULL) //free function
				return (NULL);
			*current_token = (*current_token)->next;
			i++;
		}
		else if ((*current_token)->type >= 4 && (*current_token)->type <= 7)
		{
			redirection = ft_lstnew_redirection((*current_token)->type, (*current_token)->next->token); //free
			ft_lstadd_back_redirection(&redirection_list, redirection);
			*current_token = (*current_token)->next->next;
		}
	}
	args[i] = NULL;
	return (args);
}

t_command	*filling_cmd_list(t_token *token_list, int pipe_flag)
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
		// command = NULL;
		redirection_list = NULL;
		args = inner_filling_cmd_list(&current_token, &redirection_list);
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

t_command	*parse_input(char *str)
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
	command_list = filling_cmd_list(token_list, 0);
	return (command_list);
}
