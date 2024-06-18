/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:47:54 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/18 10:33:09 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	here_docs(char *delimiter)
{
	char	*prompt;
	int		fd2;

	fd2 = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);//1 Ecriture
	if (fd2 == -1)
		return (-1);
	while (1)
	{
		prompt = readline(">");
		if (strcmp(prompt, delimiter) == 0)
			break ;
		else
		{
			ft_putstr_fd(prompt, fd2);
			ft_putstr_fd("\n", fd2);
		}
		free(prompt);
	}
	close(fd2);
	fd2 = open("temp.txt", O_RDONLY); //0 Lecture
	if (fd2 == -1)
		return (-1);
	return (fd2);
}

static int	define_input_fd(t_data *data, int i)
{
	int		input_fd;
	char	*input_file;
	char	*delimiter;

	if (arrow_count(data[i].input.tab[0], '<') - 1 == 1)
	{
		input_file = skip_redir_symbol(data[i].input.tab[0], 0);
		if (access(input_file, F_OK) == -1)
			return (perror("Files doesn't exit"), -1);
		input_fd = open(input_file, O_RDONLY);
	}
	if (arrow_count(data[i].input.tab[0], '<') - 1 == 2)
	{
		delimiter = skip_redir_symbol(data[i].input.tab[0], 0);
		input_fd = here_docs(delimiter);
		unlink("temp.txt");
	}
	return (input_fd);
}

static int	define_output_fd(t_data *data, int i)
{
	int		output_fd;
	char	*output_file;

	output_file = skip_redir_symbol(data[i].output.tab[0], 1);
	if (arrow_count(data[i].output.tab[0], '>') - 1 == 1)
	{
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (arrow_count(data[i].output.tab[0], '>') - 1 == 2)
	{
		//check_access output file 
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return (output_fd);
}

int	redir_input(t_data *data, int i, int prev_fd)
{
	int		input_fd;

	if (data[i].input.size)
	{
		input_fd = define_input_fd(data, i);
		if (input_fd == -1)
			return (perror("Failed to open input file"), -1);
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return (perror("Failed to redirect "), close(input_fd), -1);
	}
	else if (i > 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			return (perror("Failed to duplicate previous fd"), -1);
		close(prev_fd);
	}
	return (0);
}

int	redir_output(t_data *data, int i, int tab_size, int *fds)
{
	int		output_fd;

	if (data[i].output.size)
	{
		output_fd = define_output_fd(data, i);
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
