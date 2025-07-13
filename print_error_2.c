/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:23 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/12 18:42:55 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shlvl_too_high_error(char *shlvl)
{
	write(2, "minishell: warning: shell level (", 33);
	write(2, shlvl, ft_strlen(shlvl));
	write(2, ") too high, resetting to 1\n", 27);
}