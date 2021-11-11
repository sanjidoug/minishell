#include "./minishell.h"

void ft_check_error_exit(t_parse *parse)
{
    char *str;

    if (parse->tab_arg[1] != NULL && !ft_isdigit(parse->tab_arg[1][0]))
    {
        str = ft_strdup(parse->tab_arg[1]);
        printf("sh: exit: %s: numeric argument required\n", str);
        g_exit_status = 255;
        exit(g_exit_status);
    }
    if (ft_nb_arg(parse->tab_arg) > 2)
    {
        printf("sh: exit: too many arguments\n");
        g_exit_status = 1;
    }
    else
        g_exit_status = 0;
}

void ft_check_error_ex_un(t_parse *parse)
{
    int i;
    char *nb;

    i = 1;
    while (parse->tab_arg[i] != NULL)
    {
        if (ft_isdigit(parse->tab_arg[i][0]))
        {
            nb =  ft_strdup(parse->tab_arg[i]);
            printf("sh: export: `%s': not a valid identifier\n", nb);
            free(nb);
        }
        i++;
    }
    g_exit_status = 1;
}
