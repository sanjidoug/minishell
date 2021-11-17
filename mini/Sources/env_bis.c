/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:11:00 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/16 23:59:59 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_env(char *pwd, char **env, int oldpwd)
{
	int		i;
	char	*temp;

	i = 0;
	if (oldpwd)
	{
		while (ft_var("OLDPWD", env[i]))
			i++;
		temp = ft_strjoin("OLDPWD=", pwd);
		env[i] = ft_strdup(temp);
		free(temp);
	}
	else
	{
		while (ft_var("PWD", env[i]))
			i++;
		temp = ft_strjoin("PWD=", pwd);
		env[i] = ft_strdup(temp);
		free(temp);
	}
}

int	ft_close(int index, char *str)
{
	int	i;

	i = index + 1;
	while (str[i])
	{
		if (str[i] == str[index])
			return (1);
		i++;
	}
	return (0);
}

int	ft_dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
