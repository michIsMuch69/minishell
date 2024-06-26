/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-micheldusserre <jean-micheldusserr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:46:39 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/26 15:29:31 by jean-michel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int last_exit_code = 0;

bool init_pipe(int ***pipe_tab, int size);
int close_fds(int **fds, int size);
void free_pipes(int **tab, int size);

static int ft_dup(int read_fd, int write_fd)
{
    if (read_fd != STDIN_FILENO)
        if (dup2(read_fd, STDIN_FILENO) == -1)
            return (close(read_fd), handle_error("dup read_fd", errno), -1);
    if (write_fd != STDOUT_FILENO)
        if (dup2(write_fd, STDOUT_FILENO) == -1)
            return (close(write_fd), handle_error("dup write_fd", errno), -1);
    return 0;
}

int get_cmd_path(t_data *data)
{
    char *directory;
    int ret_value;

    if (!data->args.tab)
        return (1);
    directory = NULL;
    ret_value = check_all_dirs(data, &directory);
    if (ret_value)
        return (ret_value);
    if (!directory)
        return (ft_perror("command not found\n"), 1);
    data->cmd_path = ft_concat_path(directory, data->args.tab[0]);
    free(directory);
    if (!data->cmd_path)
        return (-1);
    return (0);
}

static int exec_handler(t_data *data, int *in_out)
{
    pid_t pid;
    int ret_value;

    ret_value = get_cmd_path(data);
    if (ret_value == -1 || ret_value == 1)
        return (ret_value);
    pid = fork();
    if (pid < 0)
        return (handle_error("Fork failed", errno), -1);
    if (pid > 0)
        return (pid);
    if (ft_dup(in_out[0], in_out[1]) == -1)
        exit(EXIT_FAILURE);
    if (execve(data->cmd_path, data->args.tab, data->env.tab) == -1)
        handle_error("execve failed", errno);
    return (exit(EXIT_FAILURE), 1);
}

static int init_structure(t_data *data, int *in_out)
{
    int ret_value;

    if (data->input.size || data->output.size)
    {
        ret_value = handle_redirection(in_out, data);
        if (ret_value == -1 || ret_value == 1)
            return (ret_value);
    }
    ret_value = clean_struct(data);
    if (ret_value == -1 || ret_value == 1)
        return (ret_value);
    return (0);
}

int exec(int tab_size, t_data *data)
{
    int **pipe_fd;
    int in_out_fd[2] = {0, 1};
    int status;
    pid_t pid;
    int i;

    i = 0;
    if (heredoc_management(data, tab_size) == -1)
        return (-1);
    if (tab_size > 1)
        if (init_pipe(&pipe_fd, tab_size - 1))
            return (-1);
    while (i < tab_size)
    {
        if (tab_size == 1)
        {
            status = init_structure(&(data[i]), in_out_fd);
            if (status)
                return (status);
            if (is_builtin(&data[i]))
                exec_builtin(data);
            pid = exec_handler(&(data[i]), in_out_fd);
            if (pid <= 1)
                return (pid);
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                last_exit_code = WEXITSTATUS(status);
            if (in_out_fd[0] != STDIN_FILENO)
                close(in_out_fd[0]);
            if (in_out_fd[1] != STDOUT_FILENO)
                close(in_out_fd[1]);
            in_out_fd[0] = 0;
            in_out_fd[1] = 1;
            i++;
        }
    }
    return (0);
}
