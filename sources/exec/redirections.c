/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:47:54 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/11 13:50:02 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redir_input(t_data *data, int i, int prev_fd)
{
	int		input_fd;
	char	*input_file;

	if (data[i].input.size)
	{
		input_file = skip_redir_symbol(data[i].input.tab[0], 0);
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
			return (perror("Failed to open input file"), -1);
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return (perror("Failed to redirect standard input"), close(input_fd), -1);
	}
	else if (i > 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			return (perror("Failed to duplicate previous fd for  input"), -1);
		close(prev_fd);
	}
	return (0);
}

int	redir_output(t_data *data, int i, int tab_size, int *fds)
{
	int		output_fd;
	char	*output_file;

	if (data[i].output.size)
	{
		output_file = skip_redir_symbol(data[i].output.tab[0], 1);
		if (arrow_count(data[i].output.tab[0], '>') - 1 == 1)
			output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (arrow_count(data[i].output.tab[0], '>') - 1 == 2)
			output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output_fd == -1)
			return (perror("Failed to open output file"), -1);
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return (perror("Failed to redirect standard output"), -1);
		close(output_fd);
	}
	else if (i < tab_size - 1)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (perror("Failed to duplicate pipe fd for output"), -1);
		close(fds[1]);
	}
	return (0);
}
