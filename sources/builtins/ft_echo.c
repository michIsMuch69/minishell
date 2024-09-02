/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:17:03 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/02 07:32:29 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo_print(t_data *data, int i)
{
	while (data->args.tab[i])
	{
		printf("%s", data->args.tab[i]);
		if (data->args.tab[i + 1])
			printf(" ");
		i++;
	}
	return (0);
}

int	ft_echo(t_data *data)
{
	int		flag;
	int		i;
	char	*tmp1;

	flag = 0;
	i = 1;
	if (ft_strcmp(data->args.tab[1], "cd") == 0 && \
		ft_strcmp(data->args.tab[2], "~") == 0)
	{
		if (ft_getenv("HOME", data->env.tab, &tmp1) == 0)
			return (ft_printf("cd %s\n", tmp1), free(tmp1), 0);
	}
	while (data->args.tab[i] && ft_strcmp(data->args.tab[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	ft_echo_print(data, i);
	if (!flag)
		printf("\n");
	return (0);
}
