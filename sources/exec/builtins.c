/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/26 10:04:45 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int ft_echo(char **args);
// int ft_cd(char **args);
// int ft_export(char **args);
// int ft_unset(char **args);
// int ft_env(char **env);
// int ft_exit(void);

void ft_exit(char **args)
{
	int exit_code;

	if (args[1])
	{
		exit_code = atoi(args[1]);
	}
	else
	{
		exit_code = last_exit_code;
	}
	// Cleanup et exit
	printf("Exiting shell with code: %d\n", exit_code);
	exit(exit_code);
}

int ft_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("my own pwd result : %s\n", cwd);
		return 33;
	}
	else
	{
		perror("pwd");
		return 1;
	}
}

int ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\\n", env[i]);
		i++;
	}
	return 0;
}
int	ft_cd(char **args)
{
	if (args[1] == NULL)
		return (ft_perror("No arguments to cd\n"), -1);
	else
	{
		ft_printf("This is my own cmd CD\n");;
			if (chdir(args[1]) != 0)
				perror("cd");
	}
	return (0);
}
// int	ft_pwd(void)
// {

// }