/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:18:27 by tchaloei          #+#    #+#             */
/*   Updated: 2024/12/18 16:18:27 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <termios.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_file
{
	int		re;
	char	*name;
	struct s_file *next;
}	t_file;

typedef struct s_cmd
{
	char	*program;
	char	**loaded;
	char	**command;
	char	*execute[4];
	t_file	*file;
	struct s_cmd	*pipe;
}	t_cmd;

typedef struct s_phaser
{
	t_cmd	*start;
	char	**sep;
	char	**env;
	int		export;
	int		pipe;
	int		exit;
	int		hd;
	int		pipefd[2];
	int		pipefd2[2];
}	t_phaser;

//------------handle------------//

//error_func
void	error_func(char *msg);
void	msg_error(char *file, char *msg, int flag);
void	msg_error_builtins(char *bash, char *mid, char *msg);
//all_error
int    handle_all(t_phaser *sh, t_cmd *div, int flag, int hd);
//------------phaser------------//
//phaser
void    start_phaser(t_phaser *sh, int i);
//heredoc
void	do_heredoc(t_phaser *sh, t_cmd *div, t_file *file, int i);
void	join_heredoc(t_cmd *div, int i);
//syntax
int    check_syntax(char *input, t_phaser *sh, int i);
//------------main------------//
void	ft_free_split(char **split);

//utils
int	ft_strlen2d(char **sep);
int	count_imp(char *input, char c);

//process
void    start_process(t_phaser *sh, t_cmd *div, int i, int j);
//------------builtins------------//
//builtins
int select_builtins(t_cmd *cmd);
//echo
void    do_builtins(t_phaser *sh, t_cmd *div);
//env
void    do_env(t_phaser *sh, t_cmd *div);
//export
void    do_export(t_phaser *sh, t_cmd *div);
void    export_command(t_phaser *sh, t_cmd *div);

#endif