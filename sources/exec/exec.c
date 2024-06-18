/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:46:39 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/18 10:17:31 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"



static int	exec_handler(int i, t_data *data)
{
	char	*cmd_path;
	if (!data || !data[i].args.tab)
		return (-1);
	// Expand ??
	if (is_builtin(data, i))
	{
		if (redir_output(data, i, 0, NULL) == -1)
			return (-1);
		exec_builtin(data, i);
		return (0);
	}
	else
	{
		cmd_path = format_exec_path(data, i);
		if (cmd_path != NULL)
		{
			if (execve(cmd_path, data[i].args.tab, data[i].env.tab) == -1)
				return (perror("execve failed"), free(cmd_path), -1);	
		}
		else
			  return (perror("Command not found"), -1);
	}
	return (0);
}

static int	handle_child(int i, int *fds, int tab_size, int prev_fd, t_data *data)
{
	if (redir_input(data, i, prev_fd) == -1)
		return (-1);
	if (redir_output(data, i, tab_size, fds) == -1)
		return (-1);
	if (exec_handler(i, data) == -1)
		return (-1);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
// test : 
// -  cat < file2.txt | rev > file1.txt

static void	handle_parent(int i, int *fds, int prev_fd)
{
	if (i > 0)
		close(prev_fd);
	close(fds[1]);
}

int	exec(t_data *data,int tab_size)
{
	int		i;
	int		prev_fd;
	int		fds[2];
	pid_t	pid;

	prev_fd = -1;
	i = 0;
	while (i < tab_size)
	{
		
		



		
		
		if (pipe(fds) == -1)
			return (perror("Pipe failed"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("Fork failed"), -1);
		else if (pid == 0)
			handle_child(i, fds, tab_size, prev_fd, data);
		else
		{
			handle_parent(i, fds, prev_fd);
			prev_fd = fds[0];
		}
		i++;
	}
	wait_all(tab_size);
	return (0);
}
