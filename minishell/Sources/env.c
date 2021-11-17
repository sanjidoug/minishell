/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:47:08 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 00:03:48 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_inter(int pos, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && ft_close(i++, str))
		{
			while (str[i] && str[i] != '"')
			{
				if (i++ == pos)
					return (1);
			}
		}
		if (str[i] == 39 && ft_close(i++, str))
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

void	ft_conditions(char **env, char *var, char *str, t_counter *count)
{
	var[count->j] = '\0';
	if (ft_getenv(env, var))
	{
		ft_strcat(str, ft_getenv(env, var));
		count->k += ft_strlen(ft_getenv(env, var));
		free(var);
	}
}

char	*ft_parse_line(char *line, char *var, t_counter *count, char **env)
{
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(line) + PATH_MAX + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (line[count->i])
	{
		if (line[count->i] == '$' && ft_inter(count->i, line))
		{
			var = malloc(sizeof(char) * PATH_MAX + 1);
			if (!var)
				return (NULL);
			ft_bzero(var, ft_strlen(var));
			count->i++;
			count->j = 0;
			while (line[count->i] && line[count->i] != ' '
				&& line[count->i] != '$' && !ft_is_quotes(line[count->i]))
				var[count->j++] = line[count->i++];
			ft_conditions(env, var, str, count);
		}
		else
			str[count->k++] = line[count->i++];
	}
	return (str);
}

char	*ft_var_env(char *line, char **env)
{
	t_counter	count;
	char		*var;
	char		*str;

	count.i = 0;
	count.j = 0;
	count.k = 0;
	str = ft_parse_line(line, var, &count, env);
	str[count.k] = '\0';
	return (str);
}

void	ft_set_env(t_parse *parse, char **env)
{
	int		j;
	char	*str;

	j = 0;
	while (parse->tab_arg[j] != NULL)
	{
		if (ft_dollar(parse->tab_arg[j]))
		{
			str = ft_strdup(parse->tab_arg[j]);
			free(parse->tab_arg[j]);
			parse->tab_arg[j] = ft_var_env(str, env);
			if (parse->tab_arg[j][0] == '\0')
				ft_delstr(parse->tab_arg, j--);
			free(str);
		}
		j++;
	}
}