/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:27:25 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/03 08:33:06 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	remove_env_var(t_data *data, int j)
{
	free(data->env.tab[j]);
	while (j < data->env.size - 1)
	{
		data->env.tab[j] = data->env.tab[j + 1];
		j++;
	}
	data->env.size--;
	data->env.tab[data->env.size] = NULL;
}

void	ft_unset_env(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->args.size)
	{
		j = 0;
		while (j < data->env.size)
		{
			if (ft_strncmp(data->env.tab[j], data->args.tab[i],
					ft_strlen(data->args.tab[i])) == 0)
			{
				remove_env_var(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	remove_export_var(t_data *data, int j)
{
	free(data->export.tab[j]);
	while (j < data->export.size - 1)
	{
		data->export.tab[j] = data->export.tab[j + 1];
		j++;
	}
	data->export.size--;
	data->export.tab[data->export.size] = NULL;
}

void	ft_unset_export(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->args.size)
	{
		j = 0;
		while (j < data->export.size)
		{
			if (ft_strncmp(data->export.tab[j], data->args.tab[i],
					ft_strlen(data->args.tab[i])) == 0)
			{
				remove_export_var(data, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	ft_unset(t_data *data, int i)
{
	int	y;

	ft_unset_env(&data[i]);
	ft_unset_export(&data[i]);
	y = 0;
	while (y < data[0].tab_size)
	{
		data[y].export.tab = data[i].export.tab;
		data[y].env.tab = data[i].env.tab;
		y++;
	}
	return (0);
}

//close_fds --> input output files.
//free_pipes -->  close pipes, free pipe_ptr.
