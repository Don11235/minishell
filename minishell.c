#include "minishell.h"

int main()
{
	char	*input;
	t_token *str;

	while (1)
	{
		input = readline("minishell$ "); 
		if (!input)
			break;
		str = parse_input(input);
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