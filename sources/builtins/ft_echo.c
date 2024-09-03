/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:02:51 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/03 15:24:50 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo_print(t_data *data, int i)
{
	while (data->args.tab[i])
	{
		printf("%s", data->args.tab[i]);
		if (data->args.tab[i][0] != '\0' && data->args.tab[i + 1])
			printf(" ");
		i++;
	}
	return (0);
}

int	only_n(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (data->args.tab[i] && only_n(data->args.tab[i]))
	{
		flag = 1;
		i++;
	}
	ft_echo_print(data, i);
	if (!flag)
		printf("\n");
	return (0);
}
