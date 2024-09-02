/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:50:56 by florian           #+#    #+#             */
/*   Updated: 2024/08/27 10:41:42 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

char		*clean_delimiter(char *delimiter);

static int	heredoc_loop(int fd2, char *token)
{
	char	*delimiter;
	char	*prompt;

	delimiter = clean_delimiter(skip_redir_symbol(token, 0));
	if (!delimiter)
		return (close(fd2), -2);
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			return (free(delimiter), close(fd2), 0);
		if (ft_strncmp(prompt, delimiter, ft_strlen(prompt)) == 0)
			break ;
		if (ft_putstr_fd(prompt, fd2) == -1 || \
			ft_putstr_fd("\n", fd2) == -1)
		{
			perror("putsrt_fd heredoc_loop");
			return (close(fd2), free(prompt), free(delimiter), -1);
		}
		free(prompt);
	}
	if (close(fd2) == -1)
		return (perror("close heredoc_loop"), -1);
	return (free(prompt), free(delimiter), 0);
}

static int	new_tmp_file(t_table heredoc, int hdocs_i)
{
	int		fd;
	int		fd2;
	char	tmp[9];

	ft_memset(tmp, 0, sizeof(tmp));
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (perror("open urandom "), -1);
	if (read(fd, tmp, sizeof(tmp) - 1) == -1)
		return (close(fd), perror("read urandom "), -1);
	if (close(fd) == -1)
		return (perror("close urandom fd "), -1);
	heredoc.tab[hdocs_i] = ft_strdup(tmp);
	if (!heredoc.tab[hdocs_i])
		return (ft_perror("error-> strdup heredoc\n"), -1);
	fd2 = open(heredoc.tab[hdocs_i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 == -1)
		return (perror("open heredoc file :"), -2);
	return (fd2);
}

static int	big_loop(t_data *data)
{
	int	input_i;
	int	hdocs_i;
	int	fd2;

	input_i = 0;
	hdocs_i = 0;
	while (input_i < data->input.size)
	{
		if (arrow_count(data->input.tab[input_i], '<') == 2)
		{
			fd2 = new_tmp_file(data->docs_files, hdocs_i);
			if (fd2 == -1)
				return (-1);
			if (fd2 == -2)
			{
				hdocs_i++;
				return (-1);
			}
			if (heredoc_loop(fd2, data->input.tab[input_i]) == -1)
				return (hdocs_i++, -1);
			hdocs_i++;
		}
		input_i++;
	}
	return (hdocs_i);
}

static int	init_heredocs(t_data *data)
{
	int	input_i;
	int	hdocs_i;

	input_i = 0;
	hdocs_i = 0;
	while (input_i < data->input.size)
	{
		if (arrow_count(data->input.tab[input_i], '<') == 2)
			hdocs_i++;
		input_i++;
	}
	if (hdocs_i)
	{
		data->docs_files.tab = ft_calloc(hdocs_i, sizeof(char *));
		if (!data->docs_files.tab)
		{
			data->docs_files.size = 0;
			return (ft_perror("error -> alloc heredocs"), -1);
		}
		data->docs_files.size = hdocs_i;
		return (hdocs_i);
	}
	return (0);
}

int	heredoc_management(t_data *data, int tab_size)
{
	int	ret_value;
	int	i;

	i = 0;
	while (i < tab_size)
	{
		ret_value = init_heredocs(&(data[i]));
		if (ret_value == -1)
			return (ret_value);
		if (big_loop(&(data[i])) == -1)
			return (-1);
		i++;
	}
	return (0);
}
