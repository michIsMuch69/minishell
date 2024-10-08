/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:59:06 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/05 09:47:46 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	maj_exit_status(t_data *data);

int	wait_all(t_data *data, int tab_size, int pid, int **fd)
{
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &(data[0].exit_status), 0) == -1)
	{
		free_pipes(fd, data[0].tab_size - 1);
		return (perror("wait_all waitpid() "), -1);
	}
	tab_size--;
	while (i < tab_size)
	{
		if (wait(NULL) == -1)
			return (perror("wait_all wait() "), -1);
		i++;
	}
	maj_exit_status(data);
	free_pipes(fd, data[0].tab_size - 1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
