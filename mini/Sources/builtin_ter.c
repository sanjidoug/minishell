/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:08:03 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/16 22:08:45 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_take_env(char **env, t_counter *count, char *line)
{
	char	*str;

	free(line);
	count->k = 0;
	str = malloc(sizeof(char) * ft_strlen(env[count->i]));
	if (!str)
		return (NULL);
	count->j++;
	while (env[count->i][count->j])
		str[count->k++] = env[count->i][count->j++];
	str[count->k] = '\0';
	return (str);
}

char	*ft_getenv(char **env, char *var)
{
	t_counter	count;
	char		*str;

	count.i = 0;
	while (env[count.i] != NULL)
	{
		str = malloc(sizeof(char) * ft_strlen(env[count.i]));
		if (!str)
			return (NULL);
		count.j = 0;
		count.k = 0;
		while (env[count.i][count.j] && env[count.i][count.j] != '=')
			str[count.k++] = env[count.i][count.j++];
		str[count.k] = '\0';
		if (!ft_strcmp(var, str))
			return (ft_take_env(env, &count, str));
		count.i++;
	}
	return (NULL);
}
