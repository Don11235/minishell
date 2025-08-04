/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:52:49 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 19:37:20 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_prompt_signals(void)
{
	disable_echoctl();
	set_signal(SIGINT, prompt_sigint_handler);
	set_signal(SIGQUIT, SIG_IGN);
}

static char	*read_input(char *prompt, t_env *env)
{
	char	*input;

	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5);
		free_env(env);
	}
	return (input);
}

int	main(int argc, char *argv[], char **envp)
{
	char		*input;
	t_command	*cmd;
	t_shell		shell;
	t_env		*env;

	(void)argc, (void)argv;
	shell.last_exit_status = 0;
	env = init_env(envp);
	if (!env)
		return (1);
	while (1)
	{
		setup_prompt_signals();
		input = read_input("minishell$ ", env); 
		if (!input)
			break ;
		add_history(input);
		cmd = parse_input(input, env, &shell);
		if (!cmd)
		{
			free(input);
			continue ;
		}
		(execute(cmd, env, &shell), free(input));
	}
}
