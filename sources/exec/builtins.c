/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean-micheldusserre <jean-micheldusserr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/26 17:49:21 by jean-michel      ###   ########.fr       */
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
        char *endptr;
        status = strtol(args[1], &endptr, 10);
        if (*endptr != '\0')
        {
            ft_putstr_fd("exit: numeric argument required\n", 2);
            status = 255;
        }
        else
        {
            status = status % 256;
            if (status < 0)
                status += 256;
        }
    }
    else
    {
        status = last_exit_code;
    }
    exit(status);
}



int ft_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        ft_printf("%s\n", cwd);
        return (0); 
    }
	else
	{
        handle_error("my pwd", errno);//last exit code 
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
        const char *home = getenv("HOME");
        if (home == NULL)
		{
            handle_error("my cd: HOME not set", errno);
            return (1);
        }
        if (chdir(home) == -1)
		{
            handle_error("my cd: HOME", errno);
            return (1);
        }
    }
    else if (chdir(args[1]) == -1)
    {
        handle_error("my cd: args[1]", errno);
        return (1);
    }
    return (0);
}
