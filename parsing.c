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
            if(fork() == 0)
            { 
                if (parse.tab_cmd[i][ft_strlen(parse.tab_cmd[i]) - 1] == '\n')
                   parse.tab_cmd[i][ft_strlen(parse.tab_cmd[i]) - 1] = 0;
                parse.tab_arg = ft_split(parse.tab_cmd[i], ' ');
                if (!ft_strcmp(parse.tab_arg[0],"cat"))
                    ft_cat(&parse);
                parse.tab_arg[0] = add_cmd_to_path(parse.tab_arg[0], parse.tab_path);
                execve(parse.tab_arg[0], parse.tab_arg, env);
            }
            else
                i++;
            wait(&status);
        }
        ft_free(&parse);
    }
}