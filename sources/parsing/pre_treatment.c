/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:51:51 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/15 15:34:28 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	clear_buff(char *buffer, int start, int size);

int		filter(int *i_prompt, int i_tmp, char *prompt, char *tmp);
void	skip_spaces(char *str, int *i);

// ###### PROTOTYPES ######

static char	*init_treatment(char *prompt, int *i_tmp, int i_prompt)
{
	char	*tmp;

	*i_tmp = i_prompt;
	tmp = ft_calloc(ft_strlen(prompt) + 3, sizeof(char));
	if (!tmp)
		return (free(prompt), ft_perror("error-> init pre_treatment\n"), NULL);
	tmp = ft_memcpy(tmp, prompt, ft_strlen(prompt));
	return (tmp);
}

static char	*quote_treatment(char *prompt, int *i_prompt, char c)
{
	char	*tmp;
	int		i_tmp;
	int		f_index;

	tmp = init_treatment(prompt, &i_tmp, *i_prompt);
	if (!tmp)
		return (NULL);
	tmp[i_tmp++] = 32;
	tmp[i_tmp] = prompt[(*i_prompt)];
	i_tmp++;
	while (prompt[++(*i_prompt)] && prompt[*i_prompt] != c)
		tmp[i_tmp++] = prompt[*i_prompt];
	tmp[i_tmp++] = prompt[*i_prompt];
	tmp[i_tmp++] = 32;
	f_index = i_tmp;
	while (prompt[++(*i_prompt)])
		tmp[i_tmp++] = prompt[*i_prompt];
	*i_prompt = f_index;
	clear_buff(tmp, i_tmp, (ft_strlen(prompt) + 3));
	return (free(prompt), tmp);
}

static char	*pipe_treatment(char *prompt, int *i_prompt)
{
	char	*tmp;
	int		i_tmp;
	int		f_index;

	tmp = init_treatment(prompt, &i_tmp, *i_prompt);
	if (!tmp)
		return (NULL);
	tmp[i_tmp++] = 32;
	tmp[i_tmp++] = '|';
	tmp[i_tmp++] = 32;
	f_index = i_tmp;
	(*i_prompt)++;
	skip_spaces(prompt, i_prompt);
	while (prompt[(*i_prompt)])
	{
		tmp[i_tmp] = prompt[(*i_prompt)++];
		i_tmp++;
	}
	*i_prompt = f_index;
	clear_buff(tmp, i_tmp, (ft_strlen(prompt) + 3));
	return (free(prompt), tmp);
}

static char	*redir_treatment(char *prompt, int *i_prompt, char c)
{
	char	*tmp;
	int		i_tmp;

	tmp = init_treatment(prompt, &i_tmp, *i_prompt);
	if (!tmp)
		return (NULL);
	tmp[i_tmp++] = 32;
	while (prompt[*i_prompt] && prompt[*i_prompt] == c)
	{
		tmp[i_tmp] = prompt[*i_prompt];
		(*i_prompt)++;
		i_tmp++;
	}
	*i_prompt = filter(i_prompt, i_tmp, prompt, tmp);
	return (free(prompt), tmp);
}

char	*pre_treatment(char *prompt, int i)
{
	while (prompt[i])
	{
		if (prompt[i] == '|')
		{
			prompt = pipe_treatment(prompt, &i);
			if (!prompt)
				return (NULL);
		}
		else if (prompt[i] == '"' || prompt[i] == '\'')
		{
			prompt = quote_treatment(prompt, &i, prompt[i]);
			if (!prompt)
				return (NULL);
		}
		else if (prompt[i] == '<' || prompt[i] == '>')
		{
			prompt = redir_treatment(prompt, &i, prompt[i]);
			if (!prompt)
				return (NULL);
		}
		else
			i++;
	}
	return (prompt);
}
