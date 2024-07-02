/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:46:50 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/02 11:47:38 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin_parent(t_data *data)
{
	if (ft_strcmp(data->args.tab[0], "cd") == 0)
		return (1);
	if (ft_strcmp(data->args.tab[0], "exit") == 0)
		return (1);
	if (ft_strcmp(data->args.tab[0], "export") == 0)
		return (1);
	if (ft_strcmp(data->args.tab[0], "unset") == 0)
		return (1);
	return (0);
}

int	is_builtin_child(t_data *data)
{
	if (ft_strcmp(data->args.tab[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(data->args.tab[0], "echo") == 0)
		return (1);
	if (ft_strcmp(data->args.tab[0], "env") == 0)
		return (1);
	return (0);
}

/*
  ###### TEST A FAIRE ######
  -> avant de exit(status)
	- il faut close les fd de data : free_fds(NULL, 0, data->in_out);
	- il faut free pipe_ptr avant de exit(status); free_pipes(pipe_ptr, (tab_size - 1))
*/

void	exec_builtin_parent(t_data *data)
{
	int	status;

	status = 0;
	if (ft_strcmp(data->args.tab[0], "cd") == 0)
	{
		status = ft_cd(data->args.tab);
		return ;
		// cd doesn't exit the shell, so no exit(status) at the end.
	}
	else if (ft_strcmp(data->args.tab[0], "exit") == 0)
	{
		ft_exit(data->args.tab, data->exit_code);
	}
	// else if (ft_strcmp(data->args.tab[0], "export") == 0)
	// {
	//     status = ft_export(data->args.tab);
	//     return;  // cd doesn't exit the shell, so no exit(status) at the end.
	// }
	// else if (ft_strcmp(data->args.tab[0], "unset") == 0)
	// {
	//     status = ft_unset(data->args.tab);
	//     return;  // cd doesn't exit the shell, so no exit(status) at the end.
	// }
	// only exit the shell if the exit command is called
	exit(status);
}

void	exec_builtin_child(t_data *data, int **pipe_ptr, int tab_size)
{
	int	status;

	status = 0;
	if (ft_strcmp(data->args.tab[0], "pwd") == 0)
	{
		status = ft_pwd();
	}
	// else if (ft_strcmp(data->args.tab[0], "echo") == 0)
	// {
	//     status = ft_echo(data->args.tab);
	// }
	// else if (ft_strcmp(data->args.tab[0], "env") == 0)
	// {
	//     status = ft_env(data->env.tab);
	// }
	close_fds(NULL, 0, data->in_out_fd);
	free_pipes(pipe_ptr, tab_size - 1);
	exit(status);
}
