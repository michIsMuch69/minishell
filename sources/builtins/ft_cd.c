/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:54 by jedusser          #+#    #+#             */
/*   Updated: 2024/09/02 15:06:17 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "includes.h"

char	*save_current_directory(void)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		old_pwd = getenv("PWD");
		if (!old_pwd)
		{
			ft_putstr_fd("cd: error retrieving current directory\n", 2);
			return (NULL);
		}
		old_pwd = ft_strdup(old_pwd);
	}
	return (old_pwd);
}

char	*update_current_directory(char *new_dir, char *old_pwd)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		if (new_dir[0] == '/')
			current_pwd = ft_strdup(new_dir);
		if (!current_pwd)
			return (NULL);
		else
		{
			current_pwd = ft_strjoin(old_pwd, "/");
			if (!current_pwd)
				return (NULL);
			current_pwd = ft_strcat(current_pwd, new_dir);
		}
	}
	return (current_pwd);
}

int	change_directory(t_data *data, char *old_pwd, char *new_dir)
{
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		free(old_pwd);
		if (new_dir != data->args.tab[1])
			free(new_dir);
		return (1);
	}
	return (0);
}

static int	execute_cd(t_data *data, int i, char *new_dir, char *old_pwd)
{
	char	*current_pwd;

	if (change_directory(&data[i], old_pwd, new_dir))
		return (1);
	current_pwd = update_current_directory(new_dir, old_pwd);
	if (!current_pwd)
	{
		if (new_dir != data[i].args.tab[1])
			free(new_dir);
		free(old_pwd);
		return (1);
	}
	set_env("OLDPWD", old_pwd, data[i].env.tab);
	set_env("PWD", current_pwd, data[i].env.tab);
	data[i].env.size++;
	free(current_pwd);
	return (0);
}

int	ft_cd(t_data *data, int i)
{
	char	*new_dir;
	char	*old_pwd;

	new_dir = check_cd_args(&data[i], NULL);
	if (!new_dir)
		return (1);
	old_pwd = save_current_directory();
	if (!old_pwd)
	{
		if (new_dir != data[i].args.tab[1])
			free(new_dir);
		return (1);
	}
	if (execute_cd(data, i, new_dir, old_pwd))
		return (1);
	if (new_dir != data[i].args.tab[1])
		free(new_dir);
	free(old_pwd);
	data->exit_status = 0;
	return (data->exit_status);
}
