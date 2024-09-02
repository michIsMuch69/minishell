/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/09/02 11:11:38 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

/*
	#### parse_prompt description ####

	* pre_treatment :
		// analyse of the prompt and check syntax error
	* tokenizer
		// cut prompt as table
		// ignore unused spaces before and after token
	* init_struct
		// alloc t_data table
		// fill all tables in the structure
			-> args
			-> env
			-> input files
			-> output files
*/
int	parse_prompt(t_data **data)
{
	t_table	tokens;
	int		tab_size;
	int		ret_value;

	ret_value = pre_treatment((*data)[0].prompt);
	if (ret_value)
	{
		(*data)[0].exit_status = ret_value;
		return (0);
	}
	tokens = tokenizer((*data)->prompt);
	if (!tokens.tab)
		return (0);
	tab_size = init_struct(data, &tokens, 0, 0);
	if (tab_size == -1)
		return (free_tab(&tokens, 0), 0);
	free_tab(&tokens, 0);
	return (tab_size);
}
