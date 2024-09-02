/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:32:16 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/02 15:05:11 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*check_cd_args(t_data *data, char *new_dir)
{
	if (data->args.size > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), NULL);
	if (!data->args.tab[1] || ft_strcmp(data->args.tab[1], "~") == 0)
	{
		if (ft_getenv("HOME", data->env.tab, &new_dir) != 0)
			return (ft_putstr_fd("cd: HOME not set\n", 2), NULL);
	}
	else if (ft_strcmp(data->args.tab[1], "-") == 0)
	{
		if (ft_getenv("OLDPWD", data->env.tab, &new_dir) != 0)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
		ft_printf("%s\n", new_dir);
	}
	else
		new_dir = data->args.tab[1];
	return (new_dir);
}
