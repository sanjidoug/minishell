/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 02:26:41 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 02:34:04 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_quotes(char c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_closed_quotes(char *str, int index)
{
	char	quotes;

	quotes = str[index];
	index++;
	while (str[index])
	{
		if (str[index] == quotes)
			return (index);
		index++;
	}
	return (0);
}

int	ft_check_quotes(t_parse *parse, int i)
{
	int	j;
	int	index;

	index = 0;
	while (parse->tab_arg[i] != NULL)
	{
		j = 0;
		while (parse->tab_arg[i][j])
		{
			index++;
			if (parse->tab_arg[i][j] == parse->quotes)
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_parse_quote(t_parse *parse, t_counter *count, char *str)
{
	char	*s;
	int		i;
	int		j;
	int		save_j;

	j = 0;
	while (parse->tab_arg[count->i][count->j])
	{
		if (ft_is_quotes(parse->tab_arg[count->i][count->j])
			&& ft_closed_quotes(parse->tab_arg[count->i], count->j))
		{
			if (ft_is_quotes(parse->tab_arg[count->i][count->j]))
				parse->quotes = parse->tab_arg[count->i][count->j];
			count->j++;
			while (parse->tab_arg[count->i][count->j] != parse->quotes
				&& parse->tab_arg[count->i][count->j])
				str[count->l++] = parse->tab_arg[count->i][count->j++];
		}
		else
			str[count->l++] = parse->tab_arg[count->i][count->j];
		count->j++;
	}
}

char	*ft_quotes(t_parse *parse)
{
	t_counter	count;
	char		*str;

	count.i = 0;
	count.k = 0;
	while (parse->tab_arg[count.i] != NULL)
	{
		str = malloc(sizeof(char) * ft_strlen(parse->tab_arg[count.i]) + 1);
		if (!str)
			return (NULL);
		count.j = 0;
		count.l = 0;
		ft_parse_quote(parse, &count, str);
		str[count.l] = '\0';
		free(parse->tab_arg[count.i]);
		parse->tab_arg[count.i] = ft_strdup(str);
		free(str);
		count.i++;
	}
	return (str);
}
