/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:00:30 by mben-cha          #+#    #+#             */
/*   Updated: 2025/07/09 17:38:01 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	partition(t_env **array, int low, int high)
{
	t_env	*pivot;
	t_env	*swp;
	int		start;
	int		end;

	pivot = array[low];
	start = low;
	end = high;
	while (start < end)
	{
		while (start < high && ft_strcmp(array[start]->key, pivot->key) <= 0)
			start++;
		while (end > low && ft_strcmp(array[end]->key, pivot->key) > 0)
			end--;
		if (start < end)
		{
			swp = array[start];
			array[start] = array[end];
			array[end] = swp;
		}
	}
	swp = array[low];
	array[low] = array[end];
	array[end] = swp;
	return (end); 
}

void	quick_sort_env(t_env **array, int low, int high)
{
	int	i;

	if (low < high)
	{
		i = partition(array, low, high);
		quick_sort_env(array, low, i - 1);
		quick_sort_env(array, i + 1, high);
	}
}