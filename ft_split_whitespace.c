/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:06:28 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/04 16:46:14 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	num_substr(char const *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (*str == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if ((!(str[i] >= 9 && str[i] <= 13) && str[i] != ' ')
			&& ((str[i + 1] >= 9 && str[i + 1] <= 13) || str[i + 1] == ' '))
			count++;
		i++;
	}
	if ((str[i - 1] >= 9 && str[i - 1] <= 13) || str[i - 1] == ' ')
		return (count);
	else
		return (count + 1);
}

static size_t	len_substr(char const *sb)
{
	size_t	count;

	count = 0;
	while (!(sb[count] >= 9 && sb[count] <= 13) && sb[count] != ' '
		&& sb[count])
		count++;
	return (count);
}

static char	*dup_substr(char const *s, int *i)
{
	size_t		len;
	char		*pt;

	while ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == ' ')
		(*i)++;
	len = len_substr(s + (*i)) + 1;
	pt = (char *)malloc(len * sizeof(char));
	if (pt == NULL)
		return (NULL);
	ft_strlcpy(pt, s + (*i), len);
	while (s[(*i)] != '\0' && !(s[(*i)] >= 9 && s[(*i)] <= 13)
		&& s[(*i)] != ' ')
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

char	**ft_split_whitespace(char const *s)
{
	char	**pt;
	size_t	num;
	size_t	i;
	int		pos;

	i = 0;
	pos = 0;
	if (s == NULL)
		return (NULL);
	num = num_substr(s);
	pt = malloc((num + 1) * sizeof(char *));
	if (pt == NULL)
		return (NULL);
	while (i < num)
	{
		pt[i] = dup_substr(s, &pos);
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
