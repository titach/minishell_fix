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
		if (old[i] == '$' && old[++i] == '?')
		{
			j = 0;
			while (status[j])
			{
				div->execute[2][k++] = status[j];
				j++;
			}
			k--;
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

void    do_echo(t_phaser *sh, t_cmd *div)
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
		div->execute[2] = malloc(sizeof(char) * (ft_strlen(old) - find_exit_imp(old) + 1));
		put_exit_ss2(div, old, status);
	}
	else if (sh->exit > 99)
	{
		div->execute[2] = malloc(sizeof(char) * (ft_strlen(old) + find_exit_imp(old) + 1));
		put_exit_ss2(div, old, status);
	}
	free(status);
    free(old);
}

void    do_builtins(t_phaser *sh, t_cmd *div)
{
    if (select_builtins(div) == 10)
        do_echo(sh, div);
    else if (ft_strncmp(div->command[0], "env", ft_strlen(div->command[0])) == 0)
        do_env(sh, div);
    else if (select_builtins(div) == 20)
        do_export(sh, div);
}
