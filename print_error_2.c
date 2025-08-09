/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:23 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/09 06:07:29 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shlvl_too_high_error(char *shlvl)
{
	write(2, "minishell: warning: shell level (", 33);
	write(2, shlvl, ft_strlen(shlvl));
	write(2, ") too high, resetting to 1\n", 27);
}

int	print_unset_error(char *identifier)
{
	write(2, "minishell: unset: `", 19);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

void	print_home_not_set_error(void)
{
	write(2, "minishell: cd: HOME not set\n", 28);
}
