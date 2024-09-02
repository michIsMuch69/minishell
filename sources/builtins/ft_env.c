/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:17:24 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/02 15:22:29 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env.tab[i])
	{
		ft_printf("%s\n", data->env.tab[i]);
		i++;
	}
	return (0);
}

int	ft_env(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data[i].args.tab[j])
	{
		if (ft_strcmp(data[i].args.tab[j], "env") != 0)
		{
			ft_putstr_fd("env: No such file or directory\n", 2);
			return (127);
		}
		j++;
	}
	ft_print_env(&data[i]);
	return (0);
}
