/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:46:50 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/27 10:29:24 by jedusser         ###   ########.fr       */
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

void	exec_builtin(t_data *data)
{
	int	status;
	
    if (ft_strcmp(data->args.tab[0], "exit") == 0)
        ft_exit(data->args.tab, data->exit_code);
    if (ft_strcmp(data->args.tab[0], "pwd") == 0)
        status = ft_pwd();
    if (ft_strcmp(data->args.tab[0], "cd") == 0)
        status = ft_cd(data->args.tab);
	exit(status);
}
