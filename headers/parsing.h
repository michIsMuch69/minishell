/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:09:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/29 13:46:14 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "includes.h"

// main/utils.c
void	free_tab(t_table *tab, int start);

// parsing/pre_treatment.c
int		pre_treatment(char *prompt);

// parsing/tokenizer.c
t_table	tokenizer(char *prompt);

// parsing/struct_filling.c
int		init_struct(t_data **data, t_table *tokens, int start, int data_size);

#endif