#include "minishell.h"
#include <stdio.h>

char *my_getenv(char **env)
{
    t_utils utils;
    char *path;
    
    utils.i = 0;
    while(env[utils.i] != NULL)
    {  
        utils.j = 0;
        if (*env[utils.j] == 'P')
        {
            utils.k = 0;
            while(utils.k < 4)
                utils.str[utils.k++] = *env[utils.j++];
            if (!ft_strcmp(utils.str, "PATH"))
            {
                printf("fdsf\n");
                break;   
            }
        }
        utils.i++;
    }
    //printf("%c\n", *env[utils.i]);
    /*utils.i = utils.j;
    utils.cpt = 0;
    while (*env[utils.j++])
        utils.cpt++;
    path = malloc(sizeof(char) * utils.cpt);
    utils.j = 0;
    while (utils.i < utils.cpt)
        path[utils.j++] = *env[utils.i++];
    printf("%s\n", path);*/
    //return(path);
}

int main(int ac, char **ar, char **env)
{
    char *str;
    char **tab_cmd;
    int i;

    while(1)
    {   
        i = 0;
        ft_putstr("my_prompt>");
        str = get_next_line(0);
        tab_cmd = ft_split(str);
        my_getenv(env);
    }
}