#include "minishell.h"
#include <stdio.h>

void valid_tokens(t_token *head)
{
	t_token *current;

	current = head;
	if (current->token[0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return;
	}
	while (current != NULL)
	{
		if (current->token[0] == '|' && current->next->token[0] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return;
		}
		if ((current->token[0] == '>' || current->token[0] == '<')
			&& (current->next->token[0] == '|'
			|| current->next->token[0] == '>' || current->next->token[0] == '<'))
		{
			printf("minishell: syntax error near unexpected token `%c%c'\n",
				current->next->token[0], current->next->token[1]);
			return;
		}
		if (current->next == NULL
			&& (current->token[0] == '>' || current->token[0] == '<'))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return;
		}
		current = current->next;
	}
}

void display_list(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        printf("%s -> ", current->token);
        current = current->next;
    }
    printf("NULL\n");
}

int main()
{
	char str[] = "  ls -l ' ddd ddd lll' < >>  |<<cat >> -e  >";
	int i;
	int j;
	char *s;
	char q;
	char rd;
	t_token *token;
	t_token *lst = NULL;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			q = str[i];
			j = i;
			i++;
			while (str[i] != q && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				printf("quote not closed");
			if (i > j)
			{
				s = ft_substr(str, j, i - j + 1);
				token = ft_lstnew(s);
				ft_lstadd_back(&lst, token);			
			}
			i++;
		}
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			rd = str[i];
			if (str[i + 1] == rd && rd != '|')
			{
				s = malloc(3);
				s[0] = str[i];
				s[1] = str[i];
				s[2] = '\0';
				token = ft_lstnew(s);
				ft_lstadd_back(&lst, token);
				i += 2;
			}
			else
			{
				s = malloc(2);
				s[0] = str[i];
				s[1] = '\0';
				token = ft_lstnew(s);
				ft_lstadd_back(&lst, token);
				i++;
			}
		}
		j = i;
		while (str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\0')
			i++;
		if (i > j)
		{
			s = ft_substr(str, j, i - j);
			token = ft_lstnew(s);
			ft_lstadd_back(&lst, token);
		}
	}
	valid_tokens(lst);
	display_list(lst);
}
