/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:05:42 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/14 00:05:42 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen2d(char **sep)
{
	int	i;

	i = 0;
	while (sep[i])
		i++;
	return (i);
}

int	count_imp(char *input, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == c)
			j++;
		i++;
	}
	return (j);
}
