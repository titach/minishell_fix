/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:46:47 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/18 18:46:47 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_exit_ss2(t_cmd *div, char *old, char *status)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (old[i])
	{
		if (old[i] == '$' && old[i + 1] == '?')
		{
			j = 0;
			while (status[j])
			{
				div->execute[2][k++] = status[j];
				j++;
			}
			k--;
			i++;
		}
		else
			div->execute[2][k] = old[i];
		k++;
		i++;
	}
	div->execute[2][k] = '\0';
}

static int	find_exit_imp(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
			j++;
		i++;
	}
	return (j);
}

void	do_echo_ss(t_phaser *sh, t_cmd *div, int exit_ss)
{
	char	*status;
	char	*old;

	if (sh->exit == 0)
		return ;
	status = ft_itoa(sh->exit);
	old = ft_strdup(div->execute[2]);
	if (sh->exit > 9 && sh->exit < 100)
		put_exit_ss2(div, old, status);
	else if (sh->exit < 10)
	{
		div->execute[2] = malloc(sizeof(char) * (ft_strlen(old)
					- exit_ss + 1));
		put_exit_ss2(div, old, status);
	}
	else if (sh->exit > 99)
	{
		div->execute[2] = malloc(sizeof(char) * (ft_strlen(old)
					+ exit_ss + 1));
		put_exit_ss2(div, old, status);
	}
	free(status);
	free(old);
}

void	cheak_dollar_msg(t_cmd *div, int i)
{
	char	q;

	while (div->execute[2][++i])
	{
		if (div->execute[2][i] == 34 || div->execute[2][i] == 39)
		{
			q = div->execute[2][i++];
			while (div->execute[2][i] && div->execute[2][i] != q)
				i++;
		}
		if (div->execute[2][i] == '$' && (div->execute[2][i + 1] == 34
			|| div->execute[2][i + 1] == 39))
			div->execute[2][i] = ' ';
	}
}

void	do_echo(t_phaser *sh, t_cmd *div, int i)
{
	int		exit_ss;
	char	q;

	while (div->execute[2][++i])
	{
		if (div->execute[2][i] == 34 || div->execute[2][i] == 39)
		{
			q = div->execute[2][i];
			while (div->execute[2][++i] && div->execute[2][i] != q)
			{
				if (div->execute[2][i] == '$' && q == 39)
					div->execute[2][i] = 13;
			}
		}
	}
	exit_ss = find_exit_imp(div->execute[2]);
	if (exit_ss > 0)
		do_echo_ss(sh, div, exit_ss);
	i = -1;
	while (div->execute[2][++i])
	{
		if (div->execute[2][i] == 13)
			div->execute[2][i] = '$';
	}
	cheak_dollar_msg(div, -1);
}
