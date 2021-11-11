#include "./minishell.h"

void ft_update_env(char *pwd, char **env, int oldpwd)
{
    int i;
    char *temp;

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

void ft_parse_line(char *line, char *tab_simple_quotes, char *var, t_counter *count, char *str, int index)
{
    while (line[count->i])
    {
        if (line[count->i] == '$' && tab_simple_quotes[index] == '0')
        {
            var = malloc(sizeof(char) * PATH_MAX + 1);
            ft_bzero(var, ft_strlen(var));
            count->i++;
            count->j = 0;
            while (line[count->i] && line[count->i] != ' ' &&  line[count->i] != '$')
                var[count->j++] = line[count->i++];
            var[count->j] = '\0';
            if (getenv(var))
            {
                ft_strcat(str, getenv(var));
                count->k += ft_strlen(getenv(var));
            }
            free(var);
        }
        else
            str[count->k++] = line[count->i++];

    }
}

char *ft_var_env(char *line, char *tab_simple_quotes, int index)
{
    t_counter count;
    char *var;
    char *str;

    count.i = 0;
    count.j = 0;
    count.k = 0;
    str = malloc(sizeof(char) * ft_strlen(line) + PATH_MAX + 1);
    str[0] = '\0';
    ft_parse_line(line, tab_simple_quotes, var, &count, str, index);
    str[count.k] = '\0';
    return (str);  
}

int ft_dollar(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

void ft_set_env(t_parse *parse)
{
    char *str;
    int j;

    j = 0;
    while (parse->tab_arg[j] != NULL)
    {
        if(ft_dollar(parse->tab_arg[j]))
        {
            str = ft_strdup(parse->tab_arg[j]);
            free(parse->tab_arg[j]);
            parse->tab_arg[j] = ft_var_env(str, parse->tab_simple_quotes, j);
        }
        j++;
    }
}