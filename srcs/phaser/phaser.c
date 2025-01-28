/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phaser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:46:54 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/12 00:46:54 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_imp(char *input, char c)
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

int	search_dollar_sign(char *tmp, int i)
{
	int		count;
	char	q;

	count = 0;
	while (tmp[++i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			q = tmp[i];
			while (tmp[++i] && tmp[i] != q)
			{
				if (q == 34 && tmp[i] == '$' && tmp[i + 1] != ' '
					&& tmp[i + 1] != 34 && tmp[i + 1] != 39 && tmp[i + 1])
					count++;
			}
		}
		if (tmp[i] == '$' && tmp[i + 1] != ' ' && tmp[i + 1])
			count++;
	}
	return (count);
}

void	data_execute(t_phaser *sh, t_cmd *div, int i)
{
	char	*tmp;
	int		count;
	char	*dup[4];

	count = search_dollar_sign(sh->sep[i], -1);
	if (count == 0)
		tmp = ft_strdup(sh->sep[i]);
	else
		tmp = make_env_var(sh, sh->sep[i], count, dup);
	check_redirect(tmp, div, -1);
	free(tmp);
	div->execute[0] = "sh";
	div->execute[1] = "-c";
	count = -1;
	while (sh->sep[i][++count])
	{
		if (sh->sep[i][count] == '<' && sh->sep[i][count - 1] == '<'
			&& sh->sep[i][count - 2] == '<' && count > 1)
			sh->sep[i][count] = ' ';
	}
	div->execute[2] = sh->sep[i];
	div->execute[3] = NULL;
	div->pipe = sh->start;
	sh->start = div;
}

void	check_pipe(char *input, t_phaser *sh, int i, int j)
{
	char	q;

	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			q = input[i];
			while (input[++i] && input[i] != q)
			{
				if (input[i] == '|')
					input[i] = 9;
			}
		}
	}
	sh->sep = ft_split(input, '|');
	sh->pipe = count_imp(input, '|') + 1;
	while (sh->sep[++j])
	{
		i = -1;
		while (sh->sep[j][++i])
		{
			if (sh->sep[j][i] == 9)
				sh->sep[j][i] = '|';
		}
	}
}

void	start_phaser(char *input, t_phaser *sh, int i)
{
	t_cmd	*div;

	check_pipe(input, sh, -1, -1);
	while (sh->sep[i])
		i++;
	sh->start = NULL;
	while (--i >= 0)
	{
		div = (t_cmd *)malloc(sizeof(t_cmd));
		if (!div)
			return ;
		div->file = NULL;
		data_execute(sh, div, i);
	}
	do_heredoc(sh, div, div->file, 0);
}
