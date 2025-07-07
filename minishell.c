#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	char		*input;
	t_command	*cmd;
	t_env		*env;

	env = init_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		input = readline("minishell$ "); 
		if (!input)
			break;
		add_history(input);
		cmd = parse_input(input, env); // when pars_input return NULL which mean fails 
		if (!cmd)
			continue ;
		execute(cmd, envp);
	}
}
