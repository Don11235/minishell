#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	char		*input;
	t_command	*cmd;
	t_shell		shell;
	t_env		*env;

	shell.last_exit_status = 0;
	env = init_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		set_signal(SIGINT, prompt_sigint_handler);
		set_signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ "); 
		if (!input)
		{
			write(1, "exit\n", 5);
			break;
		}
		add_history(input);
		cmd = parse_input(input, env); // when pars_input return NULL which mean fails 
		if (!cmd)
			continue ;
		execute(cmd, env, &shell);
	}
}
