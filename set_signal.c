/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:25:43 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/26 13:41:20 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    prompt_sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
} 

int	set_signal(int signo, void (*handler)(int))
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(signo, &sa, NULL) == -1)
		return (1);
	return (0);
}
