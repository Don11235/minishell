#include "minishell.h"

void display_list(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        printf("%s(%d) -> ", current->token, current->type);
        current = current->next;
    }
    printf("NULL\n");
}

void display_redirection_list(t_redirection *head) {
    t_redirection *current = head;
    while (current != NULL) {
        printf("%s(%d) -> ", current->filename_or_delimiter, current->type);
        current = current->next;
    }
    printf("NULL\n");
}

int main(int argc, char *argv[], char **envp)
{
	char		*input;
	t_command	*cmd;
	t_env		*env;

	env = init_env(envp);
	if (!env)
		return (1);
	while(1)
	{
		input = readline("minishell$ ");
		add_history(input);
		if (!input)
			break;
		cmd = parse_input(input, env); // when pars_input return NULL which mean fails 
		// display_list(str);
		while (cmd)
		{
			int test = 0;
			while (cmd->args[test])
			{
				printf("args : %s\n", cmd->args[test]);
				test++;
			}
			if (cmd->rds)
			{
				printf("rds : ");
				display_redirection_list(cmd->rds);
			}
			printf("pipe_in : %d\n", cmd->pipe_in);
			printf("pipe_out : %d\n", cmd->pipe_out);
			cmd = cmd->next;
			printf("\n");
		}
	}
}
