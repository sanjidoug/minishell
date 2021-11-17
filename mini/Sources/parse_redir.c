/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:07:26 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 17:10:07 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parse_file(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 2;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	if (i == 0)
		return (NULL);
	ret = malloc(sizeof(char) * i + 2 + 1);
	ret[0] = '.';
	ret[1] = '/';
	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		ret[j++] = str[i++];
	ret[j] = '\0';
	return (ret);
}

int	ft_delfile(t_parse *parse, int n, int s)
{
	int	i;

	i = 0;
	if (!parse->tab_arg[n] || parse->tab_arg[n][s] == 0)
		return (0);
	if (ft_strchr(parse->tab_arg[n] + s, '>')
		|| ft_strchr(parse->tab_arg[n] + s, '<'))
	{
		while (parse->tab_arg[n][s + i] != '<'
				&& (parse->tab_arg[n][s + i]) != '>')
			ft_delchar(parse->tab_arg[n], s + i);
	}
	else if (s == 0)
		ft_delstr(parse->tab_arg, n);
	else
	{
		while (parse->tab_arg[n][s + i] != '\0')
			ft_delchar(parse->tab_arg[n], s + i);
	}
	return (1);
}
