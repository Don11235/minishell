/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:39 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/07 18:23:29 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

int	ft_strcmp_exp(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 == NULL || s2 == NULL)
		return (1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	if (s2[i] == '\0' && (s1[i] == ' ' || (s1[i] >= 9 && s1[i] <= 13)
			|| s1[i] == '\0' || s1[i] == '/' || s1[i] == '$' || s1[i] == '"'
			|| s1[i] == '\'' || s1[i] == '.' || s1[i] == ',' || s1[i] == ';'
			|| s1[i] == ':' || s1[i] == ']' || s1[i] == ')'))
		return (0);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*p;

	i = 0;
	if (!src)
		return (NULL);
	p = malloc(ft_strlen(src) + 1);
	if (p == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin_with(char const *s1, char const *s2, char sep)
{
	size_t	len;
	size_t	len1;
	char	*pt;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len = len1 + ft_strlen(s2);
	pt = (char *)malloc((len + 2) * sizeof(char));
	if (pt == NULL)
		return (NULL);
	ft_memcpy(pt, s1, len1);
	pt[len1] = sep;
	ft_memcpy(pt + len1 + 1, s2, ft_strlen(s2));
	pt[len + 1] = '\0';
	return (pt);
}
