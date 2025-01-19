/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:47:01 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/18 17:47:01 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    check_syntax(char *input, t_phaser *sh, int i)
{
    char    q;

    while (input[++i] && input[i])
    {
        if (input[i] == 34 || input[i] == 39)
        {
            q = input[i];
            i++;
            while (input[i] && input[i] != q)
                i++;
            if (!input[i])
            {
                write(2, "Syntax error: Unterminated quoted string\n", 41);
                sh->exit = 1;
                return (1);
            }
        }
    }
    // printf("%d\n", sh->exit);
    return (0);
}
