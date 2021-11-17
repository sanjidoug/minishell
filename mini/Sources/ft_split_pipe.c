/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:01:08 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 17:01:51 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_inter_q(int pos, char *str)
{
    int	i;

    i = 0;
	while (str[i])
	{
		if (str[i] == '"' && ft_close(i++ ,str))
		{
			while (str[i] && str[i] != '"')
			{
				if (i++ == pos)
					return (0);
			}
		}
		if (str[i] == 39 && ft_close(i++ ,str))
		{
			while (str[i] && str[i] != 39)
			{
				if (i++ == pos)
					return (0);
			}
		}
		if (i++ == pos)
			return (1);
	}
	return (1);
}

char	**ft_pipe_error()
{
	g_exit_status =	258;
	ft_putstr_fd("minishell: syntax error near unexpected token `|'", 2);
	return (NULL);
}

char	*ft_laststr(char *str, char c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c && ft_inter_q(i, str))
			j = i;
		i++;
	}
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	if (str[j] == c)
		j++;
	while (str[j])
		ret[i++] = str[j++];
	ret[i] = '\0';
	return (ret);
}

char	**ft_parse_str(char *str, t_counter *count, char **tab)
{
	while (str[count->i])
	{
		if ((str[count->i] == '|' && ft_inter_q(count->i, str)))
		{
			count->l = 0;
			if (count->i == 0)
				return (ft_pipe_error());
			tab[count->k] = malloc(sizeof(char ) * (ft_strlen(str) + 1));
			if (!tab[count->k])
				return (NULL);
			while (count->j < count->i)
				tab[count->k][count->l++] = str[count->j++];
			tab[count->k][count->l] = '\0';
			if (ft_is_fill(tab[count->k], 32))
				return (ft_pipe_error());
			count->j++;
			count->k++;
		}
		count->i++;
	}
	return (tab);
}

char **ft_split_pipe(char *str)
{
	t_counter	count;
	char		**tab;

	init_count(&count);
	tab = malloc(sizeof(char *) * (ft_count(str ,'|') + 1 + 1));
	if (!tab || !str)
		return (NULL);
	ft_parse_str(str, &count, tab);
	tab[count.k++] = ft_laststr(str, '|');
	tab[count.k] = 0;
	return (tab);
}
