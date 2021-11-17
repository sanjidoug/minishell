/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:41:01 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 16:42:07 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_arg(t_parse *parse, t_counter *count, int i)
{
	while (parse->tab_arg[i][count->l])
	{
		if (parse->tab_arg[i][count->l] == '>')
		{
			if (ft_redir_out(parse, i, &parse->redo[count->j]))
				return (-1);
			count->j++;
			count->m = -1;
			break ;
		}
		else if (parse->tab_arg[i][count->l] == '<')
		{
			ft_redir_in(parse, i, &parse->redin[count->k]);
			count->k++;
			count->m = -1;
			break ;
		}
		count->l++;
	}
	return (0);
}

int	ft_search_redir(t_parse *parse, t_counter *count, int i)
{
	while (parse->tab_arg[i] != NULL)
	{
		count->l = 0;
		ft_parse_arg(parse, count, i);
		if (count->m < 0)
			break ;
		i++;
	}
	if (count->m < 0)
		return (1);
	return (0);
}

int	ft_redirection(t_parse *parse)
{
	t_counter	count;

	init_count(&count);
	while (parse->tab_arg[count.i] != NULL)
	{	
		count.j += ft_count(parse->tab_arg[count.i], '>');
		count.k += ft_count(parse->tab_arg[count.i++], '<');
	}
	parse->redo = malloc(sizeof(t_redo) * (count.j + 1));
	parse->redin = malloc(sizeof(t_redo) * (count.k + 1));
	init_count(&count);
	while (parse->tab_arg[count.i] != NULL)
	{
		count.m = 0;
		count.m = ft_search_redir(parse, &count, count.i);
		if (count.m > 0)
			count.i = 0;
		else if (count.m == 0)
			count.i++;
		else
			return (1);
	}
	parse->redo[count.j].append = -100;
	parse->redin[count.k].append = -100;
	return (0);
}

int	ft_redir_in(t_parse *parse, int index, t_redo *redin)
{
	int	i;

	i = 0;
	parse->redir_in = 1;
	redin->append = 0;
	while (parse->tab_arg[index][i] != '<')
		i++;
	ft_delchar(parse->tab_arg[index], i);
	if (parse->tab_arg[index][i] == '<')
		redin->append = ft_delchar(parse->tab_arg[index], i);
	if (parse->tab_arg[index][i] == 0)
	{
		if (i == 0)
			ft_delstr(parse->tab_arg, index);
		else
			index++;
		i = 0;
	}
	redin->file = ft_parse_file(parse->tab_arg[index] + i);
	ft_delfile(parse, index, i);
	if (!redin->file || redin->file[0] == 0)
		return (printf("msh: syntax error near unexpected token `newline'/\n"));
	return (0);
}

int	ft_redir_out(t_parse *parse, int index, t_redo *redo)
{
	int	i;

	i = 0;
	parse->redir_out = 1;
	redo->append = 0;
	while (parse->tab_arg[index][i] != '>')
		i++;
	ft_delchar(parse->tab_arg[index], i);
	if (parse->tab_arg[index][i] == '>')
		redo->append = ft_delchar(parse->tab_arg[index], i);
	if (parse->tab_arg[index][i] == 0)
	{
		if (i == 0)
			ft_delstr(parse->tab_arg, index);
		else
			index++;
		i = 0;
	}
	redo->file = ft_parse_file(parse->tab_arg[index] + i);
	ft_delfile(parse, index, i);
	if (!redo->file || redo->file[0] == 0)
		return (printf("msh: syntax error near unexpected token `newline'/\n"));
	return (0);
}
