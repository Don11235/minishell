/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:02:05 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/20 18:23:46 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*pt;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	pt = (char *)malloc((len + 1) * sizeof(char));
	if (pt == NULL)
		return (NULL);
	ft_memcpy(pt, s1, ft_strlen(s1));
	ft_memcpy(pt + ft_strlen(s1), s2, ft_strlen(s2));
	pt[len] = '\0';
	return (pt);
}
