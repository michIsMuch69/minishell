/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-micheldusserre <jean-micheldusserr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/18 16:34:55 by jean-michel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int ft_echo(char **args);
// int ft_cd(char **args);
// int ft_export(char **args);
// int ft_unset(char **args);
// int ft_exit(void);
// int ft_env(char **env);
// int	ft_pwd(void);

void ft_exit(int status)
{
    if (isatty(STDIN_FILENO))
	{
        printf("Close terminal\n");
        kill(0, SIGHUP);
    }
    exit(status);
}

// int	ft_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// }

int	ft_cd(char **args)
{
	if (args[1] == NULL)
		return (ft_perror("No arguments to cd\n"), -1);
	else
	{
		ft_printf("This is my own cmd CD\n");
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	return (0);
}

