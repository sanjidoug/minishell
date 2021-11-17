#include "../minishell.h"

int ft_free(t_parse *parse)
{
    int i;

    i = 0;
    while(parse->tab_arg[i] != NULL)
        free(parse->tab_arg[i++]);
    if (parse->tab_arg)
        free(parse->tab_arg);   
    i = 0; 
    while (parse->tab_cmd[i] != NULL)
        free(parse->tab_cmd[i++]);
    if (parse->tab_cmd)
        free(parse->tab_cmd);
    i = 0;
    while (parse->tab_path[i] != NULL)
        free(parse->tab_path[i++]);
    if (parse->tab_path)
        free(parse->tab_path);
    return (0);
}

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    if(!tab)
        return ;
    while(tab[i] != NULL)
        free(tab[i++]);
    free(tab);
}