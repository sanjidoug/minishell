#include "./minishell.h"

int ft_nb_spaces(char *str)
{
    int nb_spaces;
    int i;

    nb_spaces = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            nb_spaces++;
        while (str[i++] == ' ');
    }
    return (nb_spaces);
}

void ft_lowercase(t_parse *parse)
{
    int i;

    i = 0;
    while (parse->tab_arg[0][i])
    {
        if (parse->tab_arg[0][i] > 64 && parse->tab_arg[0][i] < 91)
            parse->tab_arg[0][i] = parse->tab_arg[0][i] + 32;
        i++;
    }
}

int ft_nb_arg(char **tab_arg)
{
    int i;

    i = 0;
    while (tab_arg[i] != NULL)
        i++;
    return (i);
}

int ft_var(char *vr_env, char* line)
{
    int i;

    i = 0;
    if (vr_env == NULL)
        return(1);
    while(vr_env[i] && line[i])
    {
        if(vr_env[i] != line[i])
            return(1);
        i++;
    }
    if(line[i] != '=')
        return(1);
    return(0);
}