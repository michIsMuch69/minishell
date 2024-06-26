/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-micheldusserre <jean-micheldusserr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:46:50 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/26 15:28:29 by jean-michel      ###   ########.fr       */
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

void exec_builtin(t_data *data)
{
    if (ft_strcmp(data->args.tab[0], "exit") == 0)
        ft_exit(data->args.tab);
    if (ft_strcmp(data->args.tab[0], "pwd") == 0)
        last_exit_code = ft_pwd();
    if (ft_strcmp(data->args.tab[0], "cd") == 0)
        last_exit_code = ft_cd(data->args.tab);
}
