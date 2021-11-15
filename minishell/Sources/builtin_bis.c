#include "../minishell.h"

void ft_parse_tab_arg(t_parse *parse, t_counter *count, char **tab_str, char **env)
{
    while (parse->tab_arg[count->j] != NULL)
    {
        if (ft_strchr(parse->tab_arg[count->j], '=') && !ft_isdigit(parse->tab_arg[count->j][0]))
        {
            tab_str = ft_split_custom(parse->tab_arg[count->j], '=', parse);
            if(getenv(tab_str[0]))
            {
                count->k = count->i - 1;
                while (ft_var(tab_str[0], env[count->k]))
                    count->k--;
                env[count->k] = ft_strdup(parse->tab_arg[count->j]);
            }
            else
            {
                env[count->i] = ft_strdup(env[count->i - 1]);
                env[count->i - 1] = ft_strdup(parse->tab_arg[count->j]);
                count->i++;
            }
            ft_free_tab(tab_str);
        }
        count->j++;      
    }
}

void ft_export(t_parse *parse, char **env)
{
    t_counter count;
    char **tab_str;

    count.i = 0;
    count.j = 1;
    count.k = 0;

    ft_check_error_ex_un(parse);
    while (env[count.i] != NULL)
        count.i++;
    if (parse->tab_arg[1] == NULL)
    {
        while (count.k < count.i - 1)
        {
            ft_putstr_fd(env[count.k++], 1);
            write(1, "\n", 1);
        }
    }
    ft_parse_tab_arg(parse, &count, tab_str, env);
    env[count.i] = NULL;
}

void ft_parse_tab_arg2(t_parse *parse, t_counter *count, char **tab_str, int save_i, char **env)
{
    while (parse->tab_arg[count->j] != NULL)
    {   
        count->i = save_i;
        while (count->i > -1)
        {
            tab_str = ft_split_custom(env[count->i], '=', parse);
            if (!ft_strcmp(parse->tab_arg[count->j], tab_str[0]))
            {
                while (count->i < save_i)
                {
                    env[count->i] = env[count->i + 1];
                    count->i++;
                }
                break;
            }
            count->i--;
            ft_free_tab(tab_str);
        }
        count->j++;
        save_i--;
        env[count->i] = NULL;    
    }
}

void ft_unset(t_parse *parse, char **env)
{
    t_counter count;
    int save_i;
    char **tab_str;

    count.i = 0;
    count.j = 1;
    ft_check_error_ex_un(parse);
    while (env[count.i] != NULL)
        count.i++;
    count.i--;
    save_i = count.i;
    ft_parse_tab_arg2(parse, &count, tab_str, save_i, env);
}