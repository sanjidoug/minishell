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
        my_getenv(env, "PATH");
    }
}