/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phaser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:03:25 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/28 23:03:25 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	replace_imp(char m)
{
	if (m == '<')
		return (8);
	else if (m == '>')
		return (9);
	return (10);
}

static int	last_string(char end)
{
	if (end == ' ' || end == '<' || end == '>')
		return (1);
	return (0);
}

int	count_lengt(char *tmp, int i, char *file)
{
	int		count;
	char	q;

	count = 0;
	while (tmp[++i] && last_string(tmp[i]) == 0)
	{
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			q = tmp[i];
			while (tmp[++i] && tmp[i] != q)
			{
				file[count] = tmp[i];
				count++;
			}
		}
		else
		{
			file[count] = tmp[i];
			count++;
		}
	}
	file[count] = '\0';
	return (count);
}

char	*convert_ds(t_phaser *sh, char *tmp, int start, int end)
{
	char	*envp;
	char	*sub;

	envp = NULL;
	if (tmp[start] == 34 || tmp[start++] == 39)
		envp = ft_substr(tmp, start, end - start);
	else
	{
		sub = ft_substr(tmp, start - 1, end - start + 2);
		envp = getenv(sub);
		if (!envp && tmp[start - 1] == '?')
			envp = ft_itoa(sh->exit);
		else if (!envp)
			envp = ft_strdup("\0");
		else
			envp = ft_strdup(envp);
		free(sub);
	}
	return (envp);
}
