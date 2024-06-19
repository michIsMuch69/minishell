/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/19 12:18:03 by jedusser         ###   ########.fr       */
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
	while(str[i])
	{
		if(str[i] <= '0' || str[i] >= '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data, int i)
{
	int	exit_status;
	
	exit_status = EXIT_FAILURE;

	if (data[i].args.size > 2)
	{
		exit_status = 126;
		return (ft_perror("exit: too many arguments\n"), exit_status);
	}
	if (ft_is_number(data[i].args.tab[1]) == 0)
	{
		//ft_printf("its not a num !");
		exit_status = 128;
		return (ft_perror("numeric argument required\n"), exit_status);

	}
	// close_term(); 
    return (exit_status);
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

