#include "minishell.h"

void display_list(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        printf("%s(%d) -> ", current->token, current->type);
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
	// while (1)
	// {
	// 	input = readline("minishell$ "); 
	// 	if (!input)
	// 		break;
	// 	add_history(input);
	// 	cmd = parse_input(input); // when pars_input return NULL which mean fails 
	// 	if (!cmd)
	// 		continue ;
	// 	execute(cmd, envp);
	// }
}
