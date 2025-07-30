/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:16:05 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/23 19:16:13 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp1;
	const unsigned char	*tmp2;

	if (dest == src)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	tmp1 = (unsigned char *)dest;
	tmp2 = (const unsigned char *)src;
	while (n--)
		*tmp1++ = *tmp2++;
	return (dest);
}