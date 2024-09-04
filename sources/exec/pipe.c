/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:42:26 by florian           #+#    #+#             */
/*   Updated: 2024/09/04 15:33:38 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_pipes(int **tab, int size)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < size)
	{
		if (tab[i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
}

static int	**init(int size)
{
	int	**tab;

	if (size > 508)
		return (ft_perror("error -> too much pipes\n"), NULL);
	tab = malloc(size * sizeof(int *));
	if (!tab)
		return (ft_perror("error -> alloc fd\n"), NULL);
	return (tab);
}

int	**init_pipe(int size)
{
	int	i;
	int	**pipe_tab;

	i = -1;
	pipe_tab = init(size);
	if (!pipe_tab)
		return (NULL);
	while (++i < size)
	{
		pipe_tab[i] = malloc(2 * sizeof(int));
		if (!pipe_tab[i])
			return (free_pipes(pipe_tab, i), \
			ft_perror("error -> alloc fd\n"), NULL);
	}
	i = -1;
	while (++i < size)
	{
		if (pipe(pipe_tab[i]) == -1)
		{
			close_fds(pipe_tab, i, 0, 0);
			return (free_pipes(pipe_tab, size), \
			ft_perror("init pipe\n"), NULL);
		}
	}
	return (pipe_tab);
}
