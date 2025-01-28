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
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"

extern int	g_ss;

typedef struct s_file
{
	int				re;
	char			*name;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**loaded;
	char			**command;
	char			*execute[4];
	t_file			*file;
	struct s_cmd	*pipe;
}	t_cmd;

typedef struct s_phaser
{
	t_cmd	*start;
	pid_t	*pids;
	char	**sep;
	char	**env;
	char	**export;
	int		status;
	int		stop;
	int		pipe;
	int		exit;
	int		hd;
	int		pipefd[2];
	int		pipefd2[2];
}	t_phaser;

//------------handle------------//
//error_func
void		error_func(char *msg);
void		msg_error(char *file, char *msg, int flag);
void		msg_error_builtins(char *bash, char *mid, char *msg);
//all_error
int			handle_all(t_phaser *sh, t_cmd *div, int flag, int hd);
//------------phaser------------//
//phaser
void		start_phaser(char *input, t_phaser *sh, int i);
//phaser_re
void		check_redirect(char *tmp, t_cmd *div, int i);
//phaser_env
char		*make_env_var(t_phaser *sh, char *sep, int n, char *tmp[4]);
//phaser_utils
char		replace_imp(char m);
int			count_lengt(char *tmp, int i, char *file);
char		*convert_ds(t_phaser *sh, char *tmp, int start, int end);
//heredoc
void		do_heredoc(t_phaser *sh, t_cmd *div, t_file *file, int i);
void		join_heredoc(t_cmd *div, int i);
//syntax
int			check_syntax(char *input, t_phaser *sh, int i);
//syntax_con
int			unexpected_msg(char *input, t_phaser *sh);
int			unexpected_err(char input, t_phaser *sh);
void		unexpected_token(char *next, size_t i, int flag);
int			token_redirect(char **re, int p, int i);
//signal
void		signal_init(int sig);
//utils
void		ft_free_split(char **split);
void		ft_free_struct(t_phaser *sh);
int			ft_strlen2d(char **sep);
long long	ft_atoll(const char *str);
//process
void		start_process(t_phaser *sh, t_cmd *div, int i, int j);
//------------builtins------------//
//builtins
int			select_builtins(t_cmd *cmd);
void		print_export(char **str, char *tmp, int i, size_t len);
void		do_export(t_phaser *sh, t_cmd *div, int exp);
void		do_builtins(t_phaser *sh, t_cmd *div);
//echo
void		do_echo(t_phaser *sh, t_cmd *div, int i);
//env
void		do_env(t_phaser *sh, t_cmd *div);
//export
void		export_cmd(t_phaser *sh, t_cmd *div, int flag, int i);
//exit
int			do_exit(t_cmd *div, int flag, long long num);
int			close_shell(t_cmd *div, int flag, long long num);
//cd
void		cd_cmd(t_phaser *sh, t_cmd *div, int flag);
//unset
void		unset_cmd(t_phaser *sh, t_cmd *div);
//built_utils
int			check_char(char *cmd, char *c);
int			c_cmp(char *input, char *cmd, int i);
void		add_new_env(t_phaser *sh, char *cmd);
void		a_to_z(char **str, t_phaser *sh, int i, int j);

#endif