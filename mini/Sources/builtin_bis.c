/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:45:07 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/16 22:05:04 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_tab_arg(t_parse *parse, t_counter *count,
			char **tab_str, char **env)
{
	while (parse->tab_arg[count->j] != NULL)
	{
		if (ft_strchr(parse->tab_arg[count->j], '=')
			&& !ft_isdigit(parse->tab_arg[count->j][0]))
		{
			tab_str = ft_split_custom(parse->tab_arg[count->j], '=', parse);
			if (tab_str[0] != NULL && ft_getenv(env, tab_str[0]))
			{
				count->k = count->i - 1;
				while (ft_var(tab_str[0], env[count->k]))
					count->k--;
				env[count->k] = ft_strdup(parse->tab_arg[count->j]);
			}
			else
			{
				env[count->i] = ft_strdup(env[count->i - 1]);
				env[count->i - 1] = ft_strdup(parse->tab_arg[count->j]);
				count->i++;
			}
			ft_free_tab(tab_str);
		}
		count->j++;
	}
}

void	ft_export(t_parse *parse, char **env)
{
	t_counter	count;
	char		**tab_str;

	count.i = 0;
	count.j = 1;
	count.k = 0;
	tab_str = NULL;
	ft_check_error_ex_un(parse);
	while (env[count.i] != NULL)
		count.i++;
	if (parse->tab_arg[1] == NULL)
	{
		while (count.k < count.i)
		{
			ft_putstr_fd(env[count.k++], 1);
			write(1, "\n", 1);
		}
	}
	ft_parse_tab_arg(parse, &count, tab_str, env);
	env[count.i] = NULL;
}

void	ft_parse_tab_arg2(t_parse *parse, t_counter *count,
			char **tab_str, char **env)
{
	while (parse->tab_arg[count->j] != NULL)
	{
		count->i = count->k;
		while (count->i > -1)
		{
			tab_str = ft_split_custom(env[count->i], '=', parse);
			if (!ft_strcmp(parse->tab_arg[count->j], tab_str[0]))
			{
				while (count->i < count->k)
				{
					env[count->i] = env[count->i + 1];
					count->i++;
				}
				break ;
			}
			count->i--;
			ft_free_tab(tab_str);
		}
		count->j++;
		count->k--;
		env[count->i] = NULL;
	}
}

void	ft_unset(t_parse *parse, char **env)
{
	t_counter	count;
	char		**tab_str;

	count.i = 0;
	count.j = 1;
	tab_str = NULL;
	ft_check_error_ex_un(parse);
	while (env[count.i] != NULL)
		count.i++;
	count.i--;
	count.k = count.i;
	ft_parse_tab_arg2(parse, &count, tab_str, env);
}
