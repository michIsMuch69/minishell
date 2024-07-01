/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:46:50 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/01 15:25:51 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_builtin(t_data *data)
{
    if (ft_strcmp(data->args.tab[0], "cd") == 0)
        return (1);
    if (ft_strcmp(data->args.tab[0], "pwd") == 0)
        return (1);
    if (ft_strcmp(data->args.tab[0], "exit") == 0)
        return (1);
    return (0);
}

/*
  ###### TEST A FAIRE ######
  -> avant de exit(status)
    - il faut close les fd de data : free_fds(NULL, 0, data->in_out);
    - il faut free pipe_ptr avant de exit(status); free_pipes(pipe_ptr, (tab_size - 1))
*/
void exec_builtin(t_data *data, int **pipe_ptr, int tab_size)
{
	int	status = 0;
	
    if (ft_strcmp(data->args.tab[0], "exit") == 0)
    {
        ft_exit(data->args.tab, data->exit_code);
    }
    if (ft_strcmp(data->args.tab[0], "pwd") == 0)
        status = ft_pwd();
    if (ft_strcmp(data->args.tab[0], "cd") == 0)
        status = ft_cd(data->args.tab);
    close_fds(NULL, 0, data->in_out_fd);
    free_pipes(pipe_ptr, tab_size -1);
	exit(status);
}
// void	exec_builtin(t_data *data, int **pipe_ptr, int tab_size)
// {
// 	int	status;
	
//     if (ft_strcmp(data->args.tab[0], "exit") == 0)
//         ft_exit(data->args.tab, data->exit_code);
//     if (ft_strcmp(data->args.tab[0], "pwd") == 0)
//         status = ft_pwd();
//     if (ft_strcmp(data->args.tab[0], "cd") == 0)
//         status = ft_cd(data->args.tab);
// 	exit(status);
// }
