/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:28:16 by jedusser          #+#    #+#             */
/*   Updated: 2024/08/28 11:51:46 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		if (ft_getenv("PWD", data->env.tab, &pwd) == 0)
		{
			ft_printf("%s\n", pwd);
			free(pwd);
		}
		else
		{
			ft_putstr_fd("pwd: error retrieving current directory\n", 2);
			data->exit_status = 1;
			return (1);
		}
	}
	data->exit_status = 0;
	return (0);
}