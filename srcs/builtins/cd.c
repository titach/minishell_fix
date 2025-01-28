/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:15 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/27 16:52:17 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_cd_error(char *path, int i, t_phaser *sh, int flag)
{
	if (flag == 1)
	{
		if (i == 1)
		{
			msg_error_builtins("bash: cd: `",
				path, "': No such file or directory\n");
		}
		else if (i == 2)
		{
			msg_error_builtins("bash: ", "cd:",
				" too many arguments\n");
		}
	}
	sh->exit = 1;
}

static char	*get_env(t_phaser *sh, char *en)
{
	int	i;

	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], en, ft_strlen(en)) == 0)
			return (ft_strchr(sh->env[i], '=') + 1);
		i++;
	}
	if (sh->env[i] == NULL)
		return (NULL);
	return (0);
}

static void	do_chdir(char *input, t_phaser *sh, int flag)
{
	if (access(input, F_OK) == -1)
		ms_cd_error(input, 1, sh, flag);
	else
	{
		if (flag == 0)
			chdir(input);
	}
}

static void	sep_cd(t_phaser *sh, t_cmd *div, char *oldpwd, int flag)
{
	char	*en;

	en = NULL;
	if (!div->command[1] || c_cmp(div->command[1], "~", 2) == 0)
	{
		en = get_env(sh, "HOME");
		do_chdir(en, sh, flag);
	}
	else if (c_cmp(div->command[1], "-", 2) == 0)
	{
		if (flag == 0)
			printf("%s\n", oldpwd);
		do_chdir(oldpwd, sh, flag);
	}
	else
		do_chdir(div->command[1], sh, flag);
}

void	cd_cmd(t_phaser *sh, t_cmd *div, int flag)
{
	char		*newpwd;
	static char	*oldpwd;

	if (div->command[0] && div->command[1] && div->command[2])
	{
		ms_cd_error("", 2, sh, flag);
		div->execute[2] = "cp 2> /dev/null";
	}
	else
	{
		sh->exit = 0;
		if (!oldpwd)
			oldpwd = getcwd(NULL, 0);
		newpwd = getcwd(NULL, 0);
		sep_cd(sh, div, oldpwd, flag);
		div->execute[2] = "cp 2> /dev/null";
		if (oldpwd != NULL)
		{
			free (oldpwd);
			oldpwd = newpwd;
		}
	}
}
