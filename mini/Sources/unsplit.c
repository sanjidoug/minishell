/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 03:00:24 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 03:24:11 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cpy_str(t_parse *parse, t_utils *utils,
			t_counter *count, char **tab_str)
{
	while (parse->tab_arg[count->i] != NULL && count->l < utils->end)
	{
		while (parse->tab_arg[count->i][count->j] && count->l < utils->end)
		{
			tab_str[count->m][count->k++]
				= parse->tab_arg[count->i][count->j++];
			count->l++;
		}
		utils->nb_spaces = 0;
		if (count->l != utils->end)
		{
			while (utils->nb_spaces++ < parse->tab_spaces[count->i])
				tab_str[count->m][count->k++] = ' ';
		}
		if (parse->tab_arg[count->i][count->j] != '\0')
			utils->save_j = count->j;
		count->i++;
		count->j = 0;
	}
}

void	ft_cl_quotes(t_parse *parse, t_utils *utils,
			t_counter *count, char **tab_str)
{
	int	save_i;
	int	index;

	if (!utils->cl_quotes)
	{
		if (ft_check_quotes(parse, count->i + 1))
		{
			utils->end = 0;
			index = ft_check_quotes(parse, count->i + 1);
			save_i = count->i;
			while (parse->tab_arg[save_i] != NULL && save_i <= index)
			{
				utils->end += ft_strlen(parse->tab_arg[save_i]);
				save_i++;
			}
			count->j = 0;
			count->l = 0;
			ft_cpy_str(parse, utils, count, tab_str);
			count->i--;
		}
	}
	tab_str[count->m++][count->k] = '\0';
}

void	ft_parse_quotes2(t_parse *parse, t_utils *utils, t_counter *count)
{
	while (parse->tab_arg[count->i][count->j])
	{
		if (ft_is_quotes(parse->tab_arg[count->i][count->j]))
		{
			parse->quotes = parse->tab_arg[count->i][count->j];
			utils->cl_quotes
				= ft_closed_quotes(parse->tab_arg[count->i], count->j);
			count->j = utils->cl_quotes;
		}
		if (!utils->cl_quotes)
			break ;
		count->j++;
	}
}

void	ft_parse_quotes(t_parse *parse, t_utils *utils,
			t_counter *count, char **tab_str)
{
	while (parse->tab_arg[count->i] != NULL)
	{
		utils->save_i = count->i;
		count->j = utils->save_j;
		utils->cl_quotes = 1;
		ft_parse_quotes2(parse, utils, count);
		count->k = 0;
		tab_str[count->m] = malloc(sizeof(char) * ft_strlen(parse->tab_cmd[0]) + 10000);
		if (!tab_str[count->m])
			return ;
		ft_cl_quotes(parse, utils, count, tab_str);
		if (parse->tab_arg[count->i][utils->save_j + 1]
				== '\0' || utils->save_j == 0)
			count->i++;
	}
}

char	**ft_unsplit(t_parse *parse)
{
	t_counter	count;
	t_utils		utils;
	char		**tab_str;

	count.i = 0;
	utils.save_j = 0;
	count.m = 0;
	tab_str = malloc(sizeof(char *) * ft_nb_arg(parse->tab_arg) + 10000);
	if (!tab_str)
		return (NULL);
	ft_parse_quotes(parse, &utils, &count, tab_str);
	tab_str[count.m] = NULL;
	return (tab_str);
}
