/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:03:17 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/03 11:10:15 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// main/utils.c
int	ft_perror(char *err_message);

static int	extract_value(char *var, char *word, char **var_content)
{
	int	i_var;
	int	i_content;

	i_content = 0;
	i_var = ft_strlen(word) + 1;
	var_content[0] = ft_calloc((ft_strlen(var) - ft_strlen(word)) + 1, \
															sizeof(char));
	if (!var_content[0])
		return (ft_perror("error-> alloc var_content\n"), -1);
	while (var[i_var])
	{
		var_content[0][i_content] = var[i_var];
		i_content++;
		i_var++;
	}
	return (0);
}

static char	*var_exist(char *word, char **env)
{
	int	i_env;
	int	i_word;
	int	i_str;

	i_str = 0;
	i_word = 0;
	i_env = 0;
	while (env[i_env])
	{
		while (word[i_word] && env[i_env][i_str])
		{
			if (word[i_word] != env[i_env][i_str++])
				break ;
			i_word++;
		}
		if (!word[i_word] && env[i_env][i_str] == '=')
			return (env[i_env]);
		i_env++;
		i_word = 0;
		i_str = 0;
	}
	return (NULL);
}

int	ft_getenv(char *word, char **env, char **var_content)
{
	char	*tmp;

	tmp = var_exist(word, env);
	if (!tmp)
	{
		*var_content = NULL;
		return (1);
	}
	return (extract_value(tmp, word, var_content));
}
