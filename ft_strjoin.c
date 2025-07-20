/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:02:05 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/20 18:02:16 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
