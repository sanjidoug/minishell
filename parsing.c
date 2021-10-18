#include "minishell.h"
#include <stdio.h>

char *my_getenv(char **env, char *elem)
{
    t_utils utils;
    int i;
    int j;
    char *cont_env;
    
    cont_env = 0;
    i = 0;
    while(env[i] != NULL)
    {  
        if (env[i][0] == elem[0])
        {
            utils.len_bequal = 0;
            j = 0;
            while(env[i][j++] != '=')
                utils.len_bequal++;
            utils.str = malloc(sizeof(char) * utils.len_bequal);
            j = 0;
            while(j < utils.len_bequal)
            {
                utils.str[j] = env[i][j];
                j++;
            }
            utils.str[j] = '\0';
            if (!ft_strcmp(utils.str, elem))
                break; 
        }
        i++;
    }
    if(env[i] != NULL)
        cont_env = ft_strdup_env(env[i], utils);
    return(cont_env);
}

char *add_cmd_to_path(char *cmd, char **tab_path)
{
    int i;
    int fd;
    char *path;

    i = 0;
    while (tab_path[i] != NULL)
    {
        path = ft_strjoin_path(tab_path[i], cmd);
        path[ft_strlen(path) - 1] = 0;
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

int main(int ac, char **ar, char **env)
{
    char **tab_arg;
    char **tab_cmd;
    int i;
    char *cont_env;
    char **tab_path;
    char *path;

    /*tab_arg = ft_split(get_next_line(0), ' ');
    cont_env = my_getenv(env, "PATH");
    path = ft_split(cont_env, ':');
    i = 0;
    while(path[i] != NULL)
    {
        printf("%s\n", path[i]);
        i++;
    }*/
    //printf("%d\n", execve("/Users/dlescart/.brew/bin", tab_arg, env));
    while(1)
    {   
        i = 0;
        ft_putstr("my_prompt>");
        cont_env = getenv("PATH");
        tab_path = ft_split(cont_env, ':');
        tab_cmd = ft_split(get_next_line(0), '|');
        while (tab_cmd[i] != NULL)
        {
            if(fork() == 0)
            {
                tab_arg = ft_split(tab_cmd[i], ' ');
                tab_arg[0] = add_cmd_to_path(tab_arg[0], tab_path);
                execve(tab_arg[0], tab_arg, env);
            }
            else
                i++;
        }
        //printf("%s\n", path);
    }
}