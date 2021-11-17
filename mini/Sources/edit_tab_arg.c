/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_tab_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 03:44:49 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 03:45:09 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_edit_tab_arg(t_parse *parse, char **tab_str)
{
    int i;
    int save_i;
    int j;

    i = 0;
    while (parse->tab_arg[i] != NULL)
    {
        if (tab_str[i][0] != '\0')
        {
            free(parse->tab_arg[i]);
            parse->tab_arg[i] = ft_strdup(tab_str[i]);
            j = 0;
            save_i = i + 1;
            while (parse->tab_arg[save_i + ft_nb_spaces(tab_str[i])] != NULL)
            {
                free(parse->tab_arg[save_i]);
                parse->tab_arg[save_i] = ft_strdup(parse->tab_arg[ft_nb_spaces(tab_str[i]) + save_i]);
                save_i++;
            }
            parse->tab_arg[save_i] = NULL;
        }
        i++;
    }
}
