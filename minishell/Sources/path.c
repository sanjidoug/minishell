/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 00:54:32 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 00:54:44 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_cmd_to_path(char *cmd, char **tab_path)
{
	int		i;
	char	*path;

	i = 0;
	path = ft_strdup("");
	while (tab_path[i] != NULL)
	{
		path = ft_strjoin_path("", cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		path = ft_strjoin_path(tab_path[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (cmd);
}
