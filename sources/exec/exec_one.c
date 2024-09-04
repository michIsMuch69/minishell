/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:04:55 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/04 13:37:31 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	init_child_sig(t_data *data);
int	init_sighandler(t_data *data);

void	maj_exit_status(t_data *data)
{
	if (WIFEXITED(data[0].exit_status))
	{
		if (WEXITSTATUS(data[0].exit_status) == 13)
		{
			data[0].exit_status = 126;
			ft_perror("Is a directory\n");
		}
		else
			data[0].exit_status = WEXITSTATUS(data[0].exit_status);
	}
	else if (WIFSIGNALED(data[0].exit_status))
	{
		if (WTERMSIG(data[0].exit_status) == SIGQUIT)
		{
			data[0].exit_status = 131;
			write(2, "Quit (core dumped)\n", 20);
		}
		else if (WTERMSIG(data[0].exit_status) == SIGINT)
		{
			data[0].exit_status = 130;
			write(1, "\n", 1);
		}
		else
			data[0].exit_status = WTERMSIG(data[0].exit_status);
	}
	else
		data[0].exit_status = -1;
}

static int	exec_child(t_data *data, int saved_std[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork exec_one "), -1);
	if (pid == 0)
	{
		init_child_sig(data);
		if (redir_file(data))
			exit(EXIT_FAILURE);
		if (execve(data->cmd_path, data->args.tab, data->env.tab) == -1)
		{
			free_struct(data, 1);
			exit(errno);
		}
	}
	else
	{
		close_all_redir(data, saved_std);
		if (waitpid(pid, &(data[0].exit_status), 0) == -1)
			return (-1);
		maj_exit_status(data);
		return (0);
	}
	return (0);
}

static int	exec_built(t_data *data, int saved_std[])
{
	int	exit_stat;

	if (save_std_fileno(data, saved_std))
		return (1);
	if (redir_file(data))
		return (1);
	exit_stat = exec_builtin(data, 0, NULL, 0);
	if (reset_std_fileno(saved_std))
		return (close_all_redir(data, saved_std), 1);
	return (close_all_redir(data, saved_std), exit_stat);
}

int	exec_one(t_data *data)
{
	int	saved_std[2];

	saved_std[0] = STDIN_FILENO;
	saved_std[1] = STDOUT_FILENO;
	if (is_builtin(data))
		return (exec_built(data, saved_std));
	else
		return (exec_child(data, saved_std));
	return (-1);
}
