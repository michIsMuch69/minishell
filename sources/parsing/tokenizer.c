/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:10:46 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/29 13:45:44 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	init_tokens(t_table *token)
{
	char	**tmp;

	if (!token->tab)
	{
		token->size = 0;
		token->tab = ft_calloc(1, sizeof(char *));
		if (!token->tab)
			return (ft_perror("error -> token memory allocation\n"), -1);
	}
	else
	{
		tmp = ft_realloc(token->tab, ((token->size + 1) * sizeof(char *)), \
									((token->size) * sizeof(char *)));
		if (!tmp)
		{
			free_tab(token, 0);
			return (ft_perror("error -> tab_arg memory allocation\n"), -1);
		}
		token->tab = tmp;
	}
	return (0);
}

t_table	tokenizer(char *prompt)
{
	t_table	token;
	int		start;
	int		i;

	i = 0;
	token.tab = NULL;
	while (prompt[i] != 0)
	{
		if (init_tokens(&token) == -1)
			return (token);
		skip_spaces(prompt, &i);
		if (prompt[i] == '\"' || prompt[i] == '\'')
			start = find_end_quote(prompt, &i, prompt[i]);
		else if (prompt[i] == '|')
			start = i++;
		else if (prompt[i] == '<' || prompt[i] == '>')
			start = find_end_redir(prompt, &i, prompt[i]);
		else
			start = find_end_word(prompt, &i);
		if (build_token(prompt, start, i, &token) == -1)
			return (free_tab(&token, 0), token);
		skip_spaces(prompt, &i);
	}
	return (token);
}
