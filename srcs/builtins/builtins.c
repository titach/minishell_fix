/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:56:31 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/19 14:58:28 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int select_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->command[0], "echo", 4) == 0 && ft_strlen(cmd->command[0]) == 4)
		return (10);
	else if (ft_strncmp(cmd->command[0], "pwd", 3) == 0 && ft_strlen(cmd->command[0]) == 3 )
		return (100);
	else if (ft_strncmp(cmd->command[0], "export", 6) == 0 && ft_strlen(cmd->command[0]) == 6)
		return (20);
	else if (ft_strncmp(cmd->command[0], "cd", 2) == 0 && ft_strlen(cmd->command[0]) == 2 )
		return (30);
	else if (ft_strncmp(cmd->command[0], "unset", 5) == 0 && ft_strlen(cmd->command[0]) == 5)
		return (40);
	else if (ft_strncmp(cmd->command[0], "exit", 4) == 0 && ft_strlen(cmd->command[0]) == 4)
		return (50);
	return (0);
}
