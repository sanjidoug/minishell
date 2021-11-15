#include "./minishell.h"

void ft_free_tab_arg(t_parse *parse)
{
    int i;

    i = 0;
    while(parse->tab_arg[i] != NULL)
        free(parse->tab_arg[i++]);
    free(parse->tab_arg);    
}

void ft_free(t_parse *parse)
{
    int i;

    i = 0;
    while (parse->tab_cmd[i] != NULL)
        free(parse->tab_cmd[i++]);
    free(parse->tab_cmd);
    i = 0;
    while (parse->tab_path[i] != NULL)
        free(parse->tab_path[i++]);
    free(parse->tab_path);

}

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i] != NULL)
        free(tab[i++]);
    free(tab);
}