/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 00:19:07 by tchaloei          #+#    #+#             */
/*   Updated: 2025/01/11 00:19:07 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_struct(t_phaser *sh)
{
	t_cmd *cmd;
	t_file	*file;

	while (sh->start)
	{
		cmd = sh->start;
		while (cmd->file)
		{
			file = cmd->file;
			if (file->re == 4)
				unlink(file->name);
			cmd->file = cmd->file->next;
			free(file->name);
			free(file);
		}
		ft_free_split(cmd->command);
		// free(cmd->program);
		sh->start = sh->start->pipe;
		free(cmd);
	}
	ft_free_split(sh->sep);
	// if (access(sh->export, F_OK) == 0)
	// 	unlink(sh->export);
	// free(sh);
}

void    check_pipe(char *input, t_phaser *sh, int i, int j)
{
	char q;

	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			q = input[i];
			while (input[++i] && input[i] != q)
			{
				if (input[i] == '|')
					input[i] = 9;
			}
		}
	}
	sh->sep = ft_split(input, '|');
	sh->pipe = count_imp(input, '|') + 1;
	while (sh->sep[++j])
	{
		i = -1;
		while (sh->sep[j][++i])
		{
			if (sh->sep[j][i] == 9)
				sh->sep[j][i] = '|';
		}
	}
}


// void	start_process(t_phaser *sh)
// {
// 	pid_t	pid;
// 	int		status;

// 	// status = 0;
// 	pid = fork();
// 	if (pid < 0)
// 		exit(1);
// 	else if (pid == 0)
// 	{
// 		//	เช็คโปรแกรมในนี้
// 		//  เช็ค command
// 		handle_all(sh, sh->start);
// 		if (execve("/bin/sh", sh->start->execute, sh->env) == -1)
// 		{
// 			perror(sh->start->command[0]);
// 			ft_free_struct(sh);
// 			ft_free_split(sh->sep);
// 			exit(127);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		sh->exit = WEXITSTATUS(status);
// 	}
// }

void	loading_process(char *input, t_phaser *sh)
{
	// t_cmd	*div;
	// t_file	*file;

	check_pipe(input, sh, -1, -1);
	start_phaser(sh, 0);
	start_process(sh, sh->start, 0, 0);
	// printf("%d\n", sh->export);
	// if (sh->export == 1)
	// 	export_command(sh, sh->start);
	ft_free_struct(sh);
	
}

void	prompt_line(t_phaser *sh)
{
	char *input;

	while (1)
	{
		// input = "ls";
		input = readline("\1\e[1;36m\2minishell > \1\e[0m\2");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			printf("exit\n");
			break ;
		}

		if (input && *input)
		{
			add_history(input);
			if (check_syntax(input, sh, -1) == 0)
			{
				loading_process(input, sh);
				// check_pipe(input, sh, -1, -1);
				// start_phaser(sh, 0);
				// start_process(sh, sh->start, 0, 0);
				// ft_free_struct(sh);
			}
		}
		free(input);
	}
}

void	get_shell_data(t_phaser *sh, char **en, int e)
{
	sh->start = NULL;
	sh->sep = NULL;
	// sh->export = "/tmp/exp_file";
	sh->export = 0;
	sh->pipe = 0;
	sh->exit = 0;
	sh->hd = 0;
	sh->pipefd[0] = 0;
	sh->pipefd[1] = 0;
	sh->pipefd2[0] = 0;
	sh->pipefd2[1] = 0;
	// (void)en;
	// (void)e;
	sh->env = (char **)malloc(sizeof(char *) * (ft_strlen2d(en) + 1));
	if (!sh->env)
		exit(1);
	while (en[++e])
		sh->env[e] = ft_strdup(en[e]);
	sh->env[e] = NULL;
}

int	main(int ac, char **av, char **en)
{
	t_phaser *sh;

	(void)ac;
	(void)av;
	sh = (t_phaser *)malloc(sizeof(t_phaser));
	if (!sh)
		exit(1);
	get_shell_data(sh, en, -1);
	prompt_line(sh);
	ft_free_split(sh->env);
	// free(sh->env);
	// ft_free_struct(sh);
	free(sh);
	// printf("end\n");
	// signal_init(1);
}
