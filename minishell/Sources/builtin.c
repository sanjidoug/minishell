#include "../minishell.h"

void ft_env(char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        ft_putstr_fd(env[i++], 1);
        write(1, "\n", 1);
    }
}

void ft_echo(t_parse *parse)
{
    int i;

    i = 1;
    if (parse->tab_arg[1] != NULL && !ft_strcmp(parse->tab_arg[1], "-n"))
        i++;
    while (parse->tab_arg[i] != NULL)
    {
        if (!ft_strcmp(parse->tab_arg[i], "$?"))
            ft_putstr_fd(ft_itoa(g_exit_status), 1);
        else
            ft_putstr_fd(parse->tab_arg[i], 1);
        write(1, " ", 1);
        i++;
    }
    if (parse->tab_arg[1] == NULL || ft_strcmp(parse->tab_arg[1], "-n"))
        write(1, "\n", 1);
    g_exit_status = 0;
}

char *ft_pwd(t_parse *parse)
{
    char *str;

    str = malloc(sizeof(char) * PATH_MAX + 1);
    str = getcwd(str, PATH_MAX);
    return(str);
}

void ft_cd(t_parse *parse, char **env)
{
    char *path;
    char pwd[PATH_MAX];
    
    if (parse->tab_arg[1] == NULL || parse->tab_arg[1][0] == '~')
        path = ft_strdup(getenv("HOME"));
    else
        path = ft_strdup(parse->tab_arg[1]);
    getcwd(pwd, PATH_MAX);
    ft_update_env(pwd, env, 1);
    if(chdir(path) == -1)
    {
        if (access(path, F_OK) == 0)
            printf("sh: cd: %s: Not a directory\n", path);
        else
            printf("sh: cd: %s: No such file or directory\n", path);
        g_exit_status = 1;
    }
    getcwd(pwd, PATH_MAX);
    ft_update_env(pwd, env, 0);
    free(path);
}