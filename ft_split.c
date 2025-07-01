/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:51:49 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/27 14:31:57 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	num_substr(char const *str, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (*str == '\0')
		return (0);
	if (c == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i + 1] == c)
			count++;
		i++;
	}
	if (str[i - 1] == c)
		return (count);
	else
		return (count + 1);
}

static size_t	len_substr(char const *sb, char c)
{
	size_t	count;

	count = 0;
	while (sb[count] != c && sb[count])
		count++;
	return (count);
}

static char	*dup_substr(char const *s, char c, int *i)
{
	size_t		len;
	char		*pt;

	while (s[*i] == c)
		(*i)++;
	len = len_substr(s + (*i), c) + 1;
	pt = (char *)malloc(len * sizeof(char));
	if (pt == NULL)
		return (NULL);
	ft_strlcpy(pt, s + (*i), len);
	while (s[(*i)] != '\0' && s[(*i)] != c)
		(*i)++;
	return (pt);
}

static void	free_allocated_memory(char **p, size_t i)
{
	while (i > 0)
	{
		free(p[i - 1]);
		i--;
	}
	free(p);
}

char	**ft_split(char const *s, char c)
{
	char	**pt;
	size_t	num;
	size_t	i;
	int		pos;

	i = 0;
	pos = 0;
	if (s == NULL)
		return (NULL);
	num = num_substr(s, c);
	pt = malloc((num + 1) * sizeof(char *));
	if (pt == NULL)
		return (NULL);
	while (i < num)
	{
		pt[i] = dup_substr(s, c, &pos);
		if (pt[i] == NULL)
		{
			free_allocated_memory(pt, i);
			return (NULL);
		}
		i++;
	}
	pt[i] = NULL;
	return (pt);
}
