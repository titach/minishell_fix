/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:54:32 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/19 00:54:32 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **copy_env(char **env, int i, int j)
{
    char **copy;

    copy = (char **)malloc(sizeof(char *) * (ft_strlen2d(env)));
    if (!copy)
		exit(1);
	while (env[++i] && env[i + 1])
	{
        copy[i] = ft_strdup(env[i]);
        j = -1;
        while (copy[i][++j])
        {
            if (copy[i][j] == '=')
            {
                copy[i][j] = 11;
                break;
            }
        }
    }
	copy[i] = NULL;
    return (copy);
}

void    export_stdout(t_phaser *sh, int i)
{
    int fd;
    char **tmp;
    char    **tmp_en;

    fd = open("/tmp/exp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
	    error_func("can not open file.");
    tmp_en = copy_env(sh->env, -1, -1);
    // printf("do export3\n");
    while (tmp_en[i])
    {
        write(fd, "declare -x ", 11);
        tmp = ft_split(tmp_en[i], 11);
        write(fd, tmp[0], ft_strlen(tmp[0]));
        write(fd, "\"", 1);
        if (tmp[1] != NULL)
            write(fd, tmp[1], ft_strlen(tmp[1]));
        write(fd, "\"", 1);
		write(fd, "\n", 1);
        i++;
    }
    ft_free_split(tmp);
    ft_free_split(tmp_en);
    close(fd);
    // printf("do export4\n");
}

void    export_stderr(t_cmd *div, int i)
{
    while (div->command[1][i])
    {
        if (i == 0)
        {
            if ((!(ft_isalpha(div->command[1][i]))))
            {
                msg_error_builtins("bash: export: `", div->command[1], "': not a valid identifier\n");
                div->execute[2] = "cp 2> /dev/null";
                break;
            }
        }
        if (!(isalpha(div->command[1][i]) || isdigit(div->command[1][i]) || div->command[1][i] == '='))
        {
            msg_error_builtins("bash: export: `", div->command[1], "': not a valid identifier\n");
            div->execute[2] = "cp 2> /dev/null";
            break;
        }
        i++;
    }
}

void    do_export(t_phaser *sh, t_cmd *div)
{
    printf("main exp\n");
    if (!div->command[1])
    {
        printf("main exp\n");
        export_stdout(sh, 0);
        div->execute[2] = "cat /tmp/exp_file | sort";
    }
    else
    {
        printf("%s\n", div->command[2]);
        export_stderr(div, 0);
        printf("%s\n", div->command[2]);
    }
    printf("%s\n", div->command[2]);
    if (ft_strnstr(div->command[2], "export", ft_strlen(div->command[2])))
    {
        printf("main expppp\n");
        sh->export = 1;
    }
}


