/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/02 11:05:41 by jedusser         ###   ########.fr       */
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

void ft_exit(char **args, int last_status)
{
    printf("My exit\n");

    int status = 0;
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

int ft_pwd(void)
{
    char cwd[1024];
	ft_printf("My pwd\n"); //last exit code 
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        ft_printf("%s\n", cwd);
        return (0); 
    }
	else
	{
        return (1);
    }
}

int ft_env(char **env)
{
	int	i;

	i = 0;
    // env process
    
    printf("My env\n");

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
          //  handle_error("my cd: HOME not set", errno);
            return (1); // back to prompt
        }
        if (chdir(home) == -1)
		{
            perror(NULL);
            return (-1); // crash minishell
        }
    }
    else if (chdir(args[1]) == -1)
    {
        perror("my cd");
        return (1);
    }
    return (0);
}


