/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-micheldusserre <jean-micheldusserr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/26 15:58:52 by jean-michel      ###   ########.fr       */
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
    int status = 0;
    if (args[1])
	{
        status = atoi(args[1]);
    }
	else
	{
        status = last_exit_code;
    }
	printf("Exited with status code : %d\n", status);
    exit(status);
}


int ft_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        ft_printf("%s\n", cwd);
        return (0); // Success
    }
	else
	{
        handle_error("my pwd", errno);// sets the last exit code 
        return (1);
    }
}


int ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s\\n", env[i]);
		i++;
	}
	return (0);
}
int ft_cd(char **args)
{
	printf("My cd\n");
    if (!args[1])
	{
        handle_error("my cd ", errno);
        return (1); 
    }
	if (chdir(args[1]) == -1)
	{
		handle_error("my cd : args[1]", errno); 
		return (1);
	}
    return (0); 
}