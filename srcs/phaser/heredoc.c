/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:34:39 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/18 01:34:39 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reverse_redirect(int re)
{
	if (re == 1)
		return (" < ");
	else if (re == 2)
		return (" > ");
	else if (re == 3)
		return (" >> ");
	return (" < ");
}

void	join_heredoc(t_cmd *div, int i)
{
	char	*tmp;
	char	*re;
	char	*space;
	t_file	*file;

	div->execute[2] = ft_strdup("\0");
	while (div->command[++i])
	{
		tmp = ft_strdup(div->execute[2]);
		free(div->execute[2]);
		space = ft_strjoin(" ", div->command[i]);
		div->execute[2] = ft_strjoin(tmp, space);
		free(space);
		free(tmp);
	}
	file = div->file;
	while (file)
	{
		re = ft_strjoin(reverse_redirect(file->re), file->name);
		tmp = ft_strdup(div->execute[2]);
		div->execute[2] = ft_strjoin(tmp, re);
		free(tmp);
		free(re);
		file = file->next;
	}
}

static void	receive_input(char *eof, char *file)
{
	int		fd;
	size_t	len;
	char	*text;
	char	*input;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		error_func("can not open file.");
	len = ft_strlen(eof);
	while (1)
	{
		input = readline("> ");
		if (ft_strlen(input) > len)
			len = ft_strlen(input);
		if (ft_strncmp(input, eof, len) == 0)
		{
			free(input);
			break ;
		}
		text = ft_strjoin(input, "\n");
		write(fd, text, ft_strlen(text));
		free(text);
		free(input);
	}
	close(fd);
}

void	do_heredoc(t_phaser *sh, t_cmd *div, t_file *file, int i)
{
	char	*tmp;
	char	*hd_file;

	while (div)
	{
		file = div->file;
		while (file)
		{
			if (file->re == 4)
			{
				tmp = ft_itoa(i);
				hd_file = ft_strjoin("/tmp/heredoc", tmp);
				free(tmp);
				receive_input(file->name, hd_file);
				free(file->name);
				file->name = ft_strdup(hd_file);
				free(hd_file);
				i++;
			}
			file = file->next;
		}
		div = div->pipe;
	}
	sh->hd = i;
}
