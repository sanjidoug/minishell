/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:02:07 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 19:03:36 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_delchar(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i] && i <= index)
		i++;
	while (str[i])
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i - 1] = 0;
	return (1);
}

int	ft_delstr(char **str, int index)
{
	if (str[index] == NULL)
		return (0);
	index++;
	while (str[index] != NULL)
	{
		free(str[index - 1]);
		str[index - 1] = ft_strdup(str[index]);
		index++;
	}
	free(str[index - 1]);
	str[index - 1] = NULL;
	return (0);
}
