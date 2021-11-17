/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:22:35 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 20:10:11 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_strs(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

void	ft_conditions_split(t_parse *parse, char c, char *s, char **split)
{
	while (*s != '\0')
	{
		parse->cpt = 0;
		if (*s != ' ')
			parse->is_not_space = 1;
		while (*s && *s == c)
		{
			if (c == ' ' && parse->is_not_space)
				parse->cpt++;
			s++;
		}
		if (parse->cpt != 0)
			parse->tab_spaces[parse->i++] = parse->cpt;
		parse->is_not_space = 1;
		parse->start = s;
		parse->len = 0;
		while (*s && *s != c)
		{
			s++;
			parse->len++;
		}
		if (*(s - 1) != c)
			split[parse->index++] = ft_substr(parse->start, 0, parse->len);
	}
}

char	**ft_split_custom(char *s, char c, t_parse *parse)
{
	char		**split;

	if (!s)
		return (NULL);
	split = (char **) malloc(((count_strs(s, c)) + 1) * sizeof(*split));
	if (!split)
		return (0);
	parse->index = 0;
	parse->tab_spaces = malloc(sizeof(int) * ft_strlen(s) + 1);
	parse->i = 0;
	parse->is_not_space = 0;
	ft_conditions_split(parse, c, s, split);
	parse->tab_spaces[parse->i] = -1;
	split[parse->index] = 0;
	return (split);
}
