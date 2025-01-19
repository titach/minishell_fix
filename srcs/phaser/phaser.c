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

void    phaser_space(char *sep, t_cmd *div, int i, int j)
{
	char q;

	while (sep[++i])
	{
		if (sep[i] == 34 || sep[i] == 39)
		{
			q = sep[i];
			while (sep[++i] && sep[i] != q)
			{
				if (sep[i] == ' ')
					sep[i] = 8;
			}
		}
	}
	div->loaded = ft_split(sep, ' ');
	i = -1;
	while (div->loaded[++i])
	{
		j = -1;
		while (div->loaded[i][++j])
		{
			if (div->loaded[i][j] == 8)
				div->loaded[i][j] = ' ';
		}
	}
}

int find_redirect(char *tmp, int *i)
{
	if (*i > 0 && tmp[*i] == '<' && tmp[(*i) - 1] == '<')
	{
		(*i)--;
		return (4);
	}
	else if (*i > 0 && tmp[*i] == '>' && tmp[(*i) - 1] == '>')
	{
		(*i)--;
		return (3);
	}
	else if (tmp[*i] == '>')
		return (2);
	else if (tmp[*i] == '<')
		return (1);
	return (0);
}

char    replace_imp(char m)
{
	if (m == '<')
		return (8);
	else if (m == '>')
		return (9);
	return (10);
}


int	last_string(char end)
{
	if (end == ' ' || end == '<' || end == '>')
		return (1);
	return (0);
}

int count_lengt(char *tmp, int i, char *file)
{
	int count;
	char    q;

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

char    *file_name(char *tmp, int i, bool fc)
{
	char *file;
	char	*flag;

	if (tmp[i] == '<' || tmp[i] == '>')
		i++;
	while (tmp[i] && tmp[i] == ' ' && fc == true)
		i++;
	flag = ft_strdup(tmp);
	file =  malloc(sizeof(char) * (count_lengt(tmp, i - 1, flag) + 1));
	//if (!file)
	//
	free(flag);
	i = count_lengt(tmp, i - 1, file);
	i = -1;
	while (file[++i])
	{
		if (file[i] == 8)
			file[i] = '<';
		else if (file[i] == 9)
			file[i] = '>';
		else if (file[i] == 10)
			file[i] = ' ';
	}
	// dollar_sign(file);
	return (file);
}

char return_imp(char m)
{
	if (m == 8)
		return ('<');
	else if (m == 9)
		return ('>');
	return (' ');
}

void	phaser_command(char *tmp, t_cmd *div, int i)
{
	while (tmp[++i])
	{
		if (tmp[i] == '<' || tmp[i] == '>')
		{
			while (tmp[i] && (tmp[i] == '<' || tmp[i] == '>'))
				tmp[i++] = ' ';
			while (tmp[i] == ' ')
				i++;
			while (tmp[i] && tmp[i] != ' ')
				tmp[i++] = ' ';
		}
	}
	div->loaded = ft_split(tmp, ' ');
	div->command = malloc(sizeof(char *) * (ft_strlen2d(div->loaded) + 1));
	i = -1;
	while (div->loaded[++i])
		div->command[i] = file_name(div->loaded[i], 0, 0);
	div->command[i] = NULL;
	ft_free_split(div->loaded);
}

void    check_redirect(char *tmp, t_cmd *div, int i)
{
	char    q;
	t_file  *file;

	while (tmp[++i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			q = tmp[i];
			while (tmp[++i] && tmp[i] != q)
			{
				if (tmp[i] == '<' || tmp[i] == '>' || tmp[i] == ' ')
					tmp[i] = replace_imp(tmp[i]);
			}
		}
	}
	i = ft_strlen(tmp);
	while (--i >= 0)
	{
		if (tmp[i] == '<' || tmp[i] == '>')
		{
			file = (t_file *)malloc(sizeof(t_file));
			//if (!file)
			//exit
			file->re = find_redirect(tmp, &i);
			file->name = file_name(tmp, i + 1, 1);
			file->next = div->file;
			div->file = file;
		}
	}
	phaser_command(tmp, div, -1);
}

	// printf("%d\n", count_redirect(sep, -1, 0));  < out ls > in -l
void    start_phaser(t_phaser *sh, int i)
{
	t_cmd   *div;
	char 	*tmp;

	while (sh->sep[i])
		i++;
	sh->start = NULL;
	while (--i >= 0)
	{
		div = (t_cmd *)malloc(sizeof(t_cmd));
		//if (!div)
		//
		div->file = NULL;
		tmp = ft_strdup(sh->sep[i]);
		check_redirect(tmp, div, -1);
		free(tmp);
		div->program = sh->sep[i];
		div->execute[0] = "sh";
		div->execute[1] = "-c";
		div->execute[2] = sh->sep[i];
		div->execute[3] = NULL;
		// printf("in phaser = [%s]\n", div->execute[2]);
		// select_program(sh, div);
		div->pipe = sh->start;
		sh->start = div;
	}
	do_heredoc(sh, div, div->file, 0);
}
