/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/03 13:16:42 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int ft_echo(char **args);
// int ft_cd(char **args);
// int ft_export(char **args);
// int ft_unset(char **args);
// int ft_env(char **env);
// int ft_exit(void);

int	is_numeric_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		i++;
	}
	if (!flag)
		ft_printf("\n");
	return (0);
	// what if ("echo "   "") ?? ;
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

void	ft_exit(char **args, int last_status)
{
	int	status;

	printf("My exit\n");
	status = 0;
	if (args[1])
	{
		if (is_numeric_str(args[1]) == 0)
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			status = 255;
		}
		else
		{
			status = ft_atoi(args[1]);
			status = status % 256;
			if (status < 0)
				status += 256;
			printf("Status in ft_exit = %d\n", status);
		}
	}
	else
	{
		printf("Status in ft_exit no agrs = %d\n", status);
		status = last_status;
	}
	exit(status);
}

int	ft_pwd(void)
{
	char	cwd[1024];
	char	*temp;

	ft_printf("My pwd\n"); //last exit code
	temp = getcwd(cwd, sizeof(cwd));
	if (temp != NULL)
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	else
		return (1);
}

int	ft_cd(char **args, char **env)
{
	char	*home;
	char	*oldpwd;
	char	*new_dir;
	char	cwd[1024];

	home = NULL;
	oldpwd = NULL;
	new_dir = NULL;
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (ft_getenv("HOME", env, &home) != 0)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (-1);
		}
		new_dir = home;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (ft_getenv("OLDPWD", env, &oldpwd) != 0)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (-1);
		}
		new_dir = oldpwd;
	}
	else
	{
		new_dir = args[1];
	}
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		free(home);
		free(oldpwd);
		return (-1);
	}
	//-> i have to upadate oldpwd and pwd env variables --> "setenv" ?
	free(home);
	free(oldpwd);
	return (0);
}
