/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:39:04 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/18 23:39:04 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    dollar_sign(char *file)
{
    char *tmp;

    if (!ft_strnstr(file, "$", ft_strlen(file)))
        return ;
    tmp = ft_strdup(file);
    free(file);

}
