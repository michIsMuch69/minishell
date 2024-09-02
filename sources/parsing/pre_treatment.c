/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:51:51 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/21 11:48:00 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_perror(char *err_message);
void	skip_spaces(const char *prompt, int *i);

int	init_flag(char c, int flag)
{
	if (c == '\"')
	{
		if (flag == 0)
			return (1);
		if (flag == 1)
			return (0);
		if (flag == 2)
			return (2);
	}
	else
	{
		if (flag == 0)
			return (2);
		if (flag == 2)
			return (0);
		if (flag == 1)
			return (1);
	}
	return (-1);
}

static int	check_pipe(char *prompt, int i)
{
	if ((prompt[i + 1] >= 0 && prompt[i + 1] <= 7) || \
		(prompt[i + 1] >= 10 && prompt[i + 1] <= 31) || \
		prompt[i + 1] == 124 || i == 0)
	{
		ft_perror("unexpected token (pipe)\n");
		return (2);
	}
	return (0);
}

static int	check_redir(char *prompt, int *i)
{
	const int	start = *i;

	while (prompt[*i] == '<' || prompt[*i] == '>')
		(*i)++;
	if (*i - start > 2)
		return (ft_perror("unexpected redir token\n"), 2);
	skip_spaces(prompt, i);
	if (prompt[*i] == '|' || prompt[*i] == '\t' || !prompt[*i])
		return (ft_perror("unexpected redir token\n"), 2);
	return (0);
}

int	pre_treatment(char *prompt)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|' && flag == 0)
		{
			if (check_pipe(prompt, i) == 2)
				return (2);
		}
		else if ((prompt[i] == '<' || prompt[i] == '>') && flag == 0)
			if (check_redir(prompt, &i) == 2)
				return (2);
		if (prompt[i] == '\"' || prompt[i] == '\'')
			flag = init_flag(prompt[i], flag);
		i++;
	}
	if (flag == 1)
		return (ft_perror("unexpected \'\"\' token\n"), 2);
	else if (flag == 2)
		return (ft_perror("unexpected \'\'\' token\n"), 2);
	return (0);
}
