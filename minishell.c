#include "minishell.h"

void display_list(t_token *head) {
    t_token *current = head;
    while (current != NULL) {
        printf("%s(%d) -> ", current->token, current->type);
        current = current->next;
    }
    printf("NULL\n");
}

int main()
{
	char	*input;
	t_token *str;

	while (1)
	{
		input = readline("minishell$ "); 
		add_history(input);
		if (!input)
			break;
		str = parse_input(input); // when pars_input return NULL which mean fails 
		// display_list(str);
	}
}

// int main()
// {
// 	char	*input;
// //	t_cmd	*cmd;

// 	while (1)
// 	{
// 		input = readline("minishell$ "); 
// 		if (!input)
// 			break;
// 		cmd = parse_input(input)
// 		if (!cmd)
// 			continue;
// 		execute(cmd);
// 	}
// }