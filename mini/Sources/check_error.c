/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:24:05 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/16 19:24:24 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_error_exit(t_parse *parse)
{
	char	*str;

	if (parse->tab_arg[1] != NULL && !ft_isdigit(parse->tab_arg[1][0]))
	{
		str = ft_strdup(parse->tab_arg[1]);
		ft_putstr_fd(ft_strjoin("minishell: exit: ", str), 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_status = 255;
		exit(g_exit_status);
	}
	if (ft_nb_arg(parse->tab_arg) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
	}
	else
		g_exit_status = 0;
}

void	ft_check_error_ex_un(t_parse *parse)
{
	int		i;
	char	*nb;

	i = 1;
	while (parse->tab_arg[i] != NULL)
	{
		if (!ft_isalpha(parse->tab_arg[i][0]))
		{
			nb = ft_strdup(parse->tab_arg[i]);
			ft_putstr_fd(ft_strjoin("minishell: ", parse->tab_arg[0]), 2);
			ft_putstr_fd(ft_strjoin(": `", nb), 2);
			ft_putstr_fd("'", 2);
			ft_putstr_fd(":  not a valid identifier\n", 2);
			free(nb);
		}
		i++;
	}
	g_exit_status = 1;
}
