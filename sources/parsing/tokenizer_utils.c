/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:59:13 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/29 13:51:56 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_perror(char *err_message);
int	init_flag(char c, int flag);

void	skip_spaces(const char *prompt, int *i)
{
	while (prompt[*i] == 32 || (prompt[*i] >= 9 && prompt[*i] <= 13))
		(*i)++;
}

int	build_token(char *prompt, int start, int end, t_table *token)
{
	int	i;
	int	tok_size;

	i = 0;
	tok_size = end - start;
	token->tab[token->size] = ft_calloc((tok_size + 1), sizeof(char));
	if (!token->tab[token->size])
		return (ft_perror("error -> token memory allocation\n"), -1);
	while (i < tok_size)
	{
		token->tab[token->size][i] = prompt[start];
		i++;
		start++;
	}
	token->size++;
	return (0);
}

int	find_end_quote(char *prompt, int *i, char c)
{
	const int	start = *i;
	int			flag;

	flag = 1;
	(*i)++;
	while (prompt[*i])
	{
		if ((prompt[*i] == 32 || prompt[*i] == 9) && !flag)
			break ;
		if ((prompt[*i] == '\'' || prompt[*i] == '\"') && flag == 0)
		{
			c = prompt[*i];
			flag = 1;
		}
		else if (prompt[*i] == c && flag == 1)
			flag = 0;
		if (prompt[*i])
			(*i)++;
		if (flag == 0 && (prompt[*i] == 32 || prompt[*i] == 9 || \
			prompt[*i] == '|' || prompt[*i] == '<' || prompt[*i] == '>'))
			break ;
		while (flag && prompt[*i] && (prompt[*i] == 32 || prompt[*i] == 9))
			(*i)++;
	}
	return (start);
}

int	find_end_redir(char *prompt, int *i, char c)
{
	const int	start = *i;

	while (prompt[*i] && prompt[*i] == c)
		(*i)++;
	skip_spaces(prompt, i);
	while (prompt[*i] && ((prompt[*i] != 32 && prompt[*i] != '|') || \
			(prompt[*i] <= 9 && prompt[*i] >= 13)))
		(*i)++;
	return (start);
}

int	find_end_word(char *prompt, int *i)
{
	const int	start = *i;
	char		c;

	while (prompt[*i])
	{
		if (prompt[*i] == 32 || prompt[*i] == '|' || \
			prompt[*i] == '<' || prompt[*i] == '>' || \
			(prompt[*i] > 9 && prompt[*i] < 13))
			break ;
		if (prompt[*i] == '\'' || prompt[*i] == '\"')
		{
			c = prompt[*i];
			(*i)++;
			while (prompt[*i] && prompt[*i] != c)
				(*i)++;
		}
		if (prompt[*i])
			(*i)++;
	}
	return (start);
}
