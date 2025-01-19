/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:36:29 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/19 00:36:29 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    do_env(t_phaser *sh, t_cmd *div)
{
    char    *tmp;
    int i;

    tmp = ft_strdup(div->execute[2]);
    div->execute[2] = ft_strjoin(tmp, " > /dev/null");
    free(tmp);
    i = 0;
    while (sh->env[i] && !div->command[1])
    {
        write(1, sh->env[i], ft_strlen(sh->env[i]));
		write(1, "\n", 1);
        i++;
    }
}
