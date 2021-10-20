#include "minishell.h"
#include <stdio.h>

char *add_cmd_to_path(char *cmd, char **tab_path)
{
    int i;
    int fd;
    char *path;

    i = 0;
    path = "";
    while (tab_path[i] != NULL)
    {
        path = ft_strjoin_path(path, cmd);
        fd = open(path, O_RDONLY);
        if (fd >= 0)
        {
            close(fd);
            return(path);
        }
        path = ft_strjoin_path(tab_path[i], cmd);
        fd = open(path, O_RDONLY);
        if (fd >= 0)
        {
            close(fd);
            return(path);
        }
        free(path);
        i++;
    }
    return (NULL);
}

void ft_free(t_parse *parse)
{
    int i;

    i = 0;
    while (parse->tab_path[i] != NULL)
        free(parse->tab_path[i++]);
    free(parse->tab_path);
    i = 0;
    while(parse->tab_cmd[i] != NULL)
        free(parse->tab_cmd[i++]);
    free(parse->tab_cmd);
}

void ft_cat(t_parse *parse)
{
    int i;

    i = 1;
    while(parse->tab_arg[i] != NULL)
    {
        if(parse->tab_arg[i][0] != '-')
            parse->tab_arg[i] = ft_strjoin_path(getenv("PWD"), parse->tab_arg[i]);
        i++;
    }
}

void ft_export(t_parse *parse, char **env)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while (env[i] != NULL)
        i++;
    while (parse->tab_arg[j] != NULL)
    {
        if (ft_strchr(parse->tab_arg[j], '='))
        {
            env[i] = env[i - 1];
            env[i - 1] = parse->tab_arg[j];
        }
        j++;
        i++;
    }
    env[i] = NULL;
}

void ft_unset(t_parse *parse, char **env)
{
    int i;
    int j;
    int save_i;
    char **str;

    i = 0;
    j = 1;
    while (env[i] != NULL)
        i++;
    save_i = i--;
    while (parse->tab_arg[j] != NULL)
    {   
        i = save_i;
        while (i > -1)
        {
            //printf("%c\n", env[i][0]);
            str = ft_split(env[i], '=');
            printf("%s\n", str[0]);
            if (!ft_strcmp(str[0], env[i]))
                env[i] = env[i + 1];
            i--;
        }
        j++;
    }
    env[i] = NULL;
}

void ft_env(char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        ft_putstr(env[i++]);
        write(1, "\n", 1);
    }
}

int main(int ac, char **ar, char **env)
{
    t_parse parse;
    int i;
    int status;
    
    while(1)
    {   
        i = 0;
        ft_putstr("my_prompt>");
        parse.cont_env = getenv("PATH");
        parse.tab_path = ft_split(parse.cont_env, ':');
        parse.tab_cmd = ft_split(get_next_line(0), '|');
        if (!ft_strcmp(parse.tab_cmd[0], "exit\n"))
        {
            ft_free(&parse);
            exit(0);
        }
        while (parse.tab_cmd[i] != NULL)
        {
            if (parse.tab_cmd[i][ft_strlen(parse.tab_cmd[i]) - 1] == '\n')
                   parse.tab_cmd[i][ft_strlen(parse.tab_cmd[i]) - 1] = 0;
            parse.tab_arg = ft_split(parse.tab_cmd[i], ' ');
            if (!ft_strcmp(parse.tab_arg[0], "export"))
                ft_export(&parse, env);
            if (!ft_strcmp(parse.tab_arg[0], "unset"))
                ft_unset(&parse, env);
            if (!ft_strcmp(parse.tab_arg[0], "env"))
                ft_env(env);
            else
            {
                if (!ft_strcmp(parse.tab_arg[0],"cat"))
                    ft_cat(&parse);
                parse.tab_arg[0] = add_cmd_to_path(parse.tab_arg[0], parse.tab_path);
                if(fork() == 0)
                    execve(parse.tab_arg[0], parse.tab_arg, env);
            }
            i++;
            wait(&status);
        }
        ft_free(&parse);
    }
}