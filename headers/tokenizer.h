/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:38:05 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/21 12:48:05 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "includes.h"

// main/utils.c
int		ft_perror(char *err_message);
void	free_tab(t_table *tab, int start);

// parsing/tokenizer_utils.c
int		build_token(char *prompt, int start, int end, t_table *token);
void	skip_spaces(const char *prompt, int *i);
int		find_end_quote(char *prompt, int *i, char c);
int		find_end_redir(char *prompt, int *i, char c);
int		find_end_word(char *prompt, int *i);

#endif