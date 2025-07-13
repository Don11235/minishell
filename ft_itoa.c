/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:19 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/12 20:37:41 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	recursive_itoa(int n, char *str, int *index)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		str[(*index)++] = '-';
		nb = -nb;
	}
	if (nb / 10)
		recursive_itoa(nb / 10, str, index);
	str[(*index)++] = (nb % 10) + '0';
}

static int	count_digit(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*pt;
	int		i;
	int		n_digit;

	i = 0;
	n_digit = count_digit(n) + 1;
	pt = (char *)malloc(n_digit * sizeof(char));
	if (pt == NULL)
		return (NULL);
	recursive_itoa(n, pt, &i);
	pt[i] = '\0';
	return (pt);
}