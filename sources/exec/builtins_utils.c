/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:46:50 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/20 10:02:46 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(t_data *data, int i)
{
	// if (ft_strcmp(data[i].args.tab[0], "echo") == 0)
	// 	return (1);
	if (ft_strcmp(data[i].args.tab[0], "cd") == 0)
		return (1);
	// if (ft_strcmp(data[i].args.tab[0], "pwd") == 0)
	// 	return (1);
	// if (ft_strcmp(data[i].args.tab[0], "export") == 0)
	// 	return (1);
	// if (ft_strcmp(data[i].args.tab[0], "unset") == 0)
	// 	return (1);
	// if (ft_strcmp(data[i].args.tab[0], "env") == 0)
	// 	return (1);
	if (ft_strcmp(data[i].args.tab[0], "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_data *data, int i)
{
	int	exit_status = EXIT_FAILURE;
	if (ft_strcmp(data[i].args.tab[0], "exit") == 0)
	{
		exit_status = ft_exit(data);
		ft_printf("exit status is : %d\n", exit_status);

		
	}	
	if (ft_strcmp(data[i].args.tab[0], "cd") == 0)
	{
		exit_status = ft_cd(data[i].args.tab);	
	}
	return (exit_status);
}