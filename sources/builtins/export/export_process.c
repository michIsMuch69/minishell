/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:26:24 by jean-michel       #+#    #+#             */
/*   Updated: 2024/09/04 12:11:51 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	init_exported_env(t_data *data)
{
	int		i;
	t_vars	vars;

	data->export.tab = ft_calloc((data->env.size + 1), sizeof(char *));
	if (!data->export.tab)
		return (1);
	i = 0;
	while (i < data->env.size)
	{
		if (process_env_var_for_export(&vars, data->env.tab[i], data, i) != 0)
			return (free(data->export.tab), free_vars(&vars), 1);
		i++;
	}
	data->export.tab[i] = NULL;
	data->export.size = data->env.size;
	return (0);
}

int	process_export_arg(int i, t_data *data)
{
	t_vars	vars;

	vars.equal_pos = ft_strchr(data->args.tab[i], '=');
	vars.key = NULL;
	vars.value = NULL;
	vars.new_var = NULL;
	if (vars.equal_pos)
	{
		if (process_full_entry(&vars, data, i) != 0)
			return (free_vars(&vars), 1);
	}
	else
	{
		if (process_uncomplete_entry(&vars, data, i) != 0)
			return (free_vars(&vars), 1);
	}
	return (0);
}

int	ft_export_args(t_data *data)
{
	int	i;

	i = 1;
	while (data->args.tab[i])
	{
		if (process_export_arg(i, data) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export_print(t_data *data)
{
	int	i;

	i = 0;
	sort_tab(&data->export);
	while (i < data->export.size)
	{
		ft_printf("declare -x %s\n", data->export.tab[i]);
		i++;
	}
	return (0);
}

int	ft_export(t_data *data)
{
	if (data->tab_size)
	{
		if (data->args.size == 1)
		{
			if (ft_export_print(data) != 0)
				return (1);
		}
		else if (ft_export_args(data) != 0)
			return (1);
	}
	return (0);
}
