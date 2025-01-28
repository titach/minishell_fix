/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:37:39 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/15 23:37:39 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(t_file *file)
{
	if (file->re == 1)
	{
		if (access(file->name, F_OK) == -1)
		{
			msg_error(file->name, ": No such file or directory\n", 1);
			return (1);
		}
		else if (access(file->name, R_OK) == -1)
		{
			msg_error(file->name, ": Permission denied\n", 1);
			return (1);
		}
	}
	else if (file->re == 2 || file->re == 3)
	{
		if (access(file->name, F_OK) == 0 && access(file->name, W_OK) == -1)
		{
			msg_error(file->name, ": Permission denied\n", 1);
			return (1);
		}
	}
	return (0);
}

static int	directory_name(t_cmd *div)
{
	DIR		*dir;
	int		flag;

	dir = NULL;
	dir = opendir(div->command[0]);
	flag = 0;
	if (access(div->command[0], X_OK) == 0 && dir)
	{
		msg_error(div->command[0], ": Is a directory\n", 1);
		div->execute[2] = "/ 2> /dev/null";
		flag = 1;
	}
	else if (access(div->command[0], X_OK) == -1 && !dir)
	{
		msg_error(div->command[0], ": No such file or directory\n", 1);
		div->execute[2] = "/notfound 2> /dev/null";
		flag = 1;
	}
	closedir(dir);
	return (flag);
}

static int	select_program(char **en, int i)
{
	char	**path;

	while (*en && ft_strncmp(*en, "PATH=", 5) != 0)
		en++;
	if (!*en)
		return (0);
	path = ft_split(*en + 5, ':');
	while (path[i])
	{
		if (ft_strnstr(path[i], "/usr/bin", ft_strlen(path[i])) == 0
			|| ft_strnstr(path[i], "/bin", ft_strlen(path[i])) == 0)
		{
			ft_free_split(path);
			return (1);
		}
		i++;
	}
	ft_free_split(path);
	return (0);
}

static int	commond_name(t_phaser *sh, t_cmd *div)
{
	char	*bin;
	char	*sbin;
	int		flag;

	flag = 0;
	if (select_program(sh->env, 0) == 0)
		directory_name(div);
	else
	{
		sbin = ft_strjoin("/usr/bin/", div->command[0]);
		bin = ft_strjoin("/bin/", div->command[0]);
		if (access(sbin, X_OK) == -1 || access(bin, X_OK) == -1
			|| div->command[0][0] == '\0')
		{
			msg_error(div->command[0], ": command not found\n", 0);
			div->execute[2] = "/notfound 2> /dev/null";
			flag = 1;
		}
		free(sbin);
		free(bin);
	}
	return (flag);
}

int	handle_all(t_phaser *sh, t_cmd *div, int flag, int hd)
{
	t_file	*file;

	file = div->file;
	while (file)
	{
		if (file->re == 4)
			hd = 1;
		if (check_file(file) == 1)
		{
			div->execute[2] = "cp 2> /dev/null";
			flag = 1;
			break ;
		}
		file = file->next;
	}
	if (flag == 0 && select_builtins(div) == 0)
	{
		if (ft_strnstr(div->command[0], "/", ft_strlen(div->command[0])))
			flag = directory_name(div);
		else
			flag = commond_name(sh, div);
	}
	if (flag == 0 && hd == 1)
		join_heredoc(div, -1);
	return (flag);
}
