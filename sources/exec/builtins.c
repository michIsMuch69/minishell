/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/20 11:37:31 by jedusser         ###   ########.fr       */
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

void	close_term(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("Close terminal\n");
		kill(0, SIGHUP);
	}
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data)
{
	int		exit_status;

	if (data->args.size > 2)
	{
		ft_perror("exit: too many arguments");
		return (-1);
	}
	if (data->args.size == 2 || data->args.size == 1)
	{
		if (data->args.size == 2)
		{
			if (!ft_is_number(data->args.tab[1]))
			{
				ft_perror("exit: numeric argument required");
				exit(2);
			}
		}
		if (isatty(STDIN_FILENO))
		{
			printf("Close terminal\n");
			kill(0, SIGHUP);
		}
			
	}
	exit_status = ft_atoi(data->args.tab[1]) % 256;
	printf("exit status in exit = %d\n", exit_status);
	exit(exit_status);
	return (0);
}

// int	ft_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// }

int	ft_cd(char **args)
{
	// retour racine
	if (args[1] == NULL)
		return (ft_perror("No arguments to cd\n"), EXIT_FAILURE);
	else
	{
		ft_printf("This is my own cmd CD\n");
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	return (EXIT_SUCCESS);
}

