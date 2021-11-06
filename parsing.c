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
    i = 0;
    while(parse->tab_arg[i] != NULL)
        free(parse->tab_arg[i++]);
    free(parse->tab_arg);
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

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i] != NULL)
        free(tab[i++]);
    free(tab);
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

void ft_export(t_parse *parse, char **env)
{
    int i;
    int j;
    int k;
    char **str;
    char **vr_env;

    i = 0;
    j = 1;
    k = 0;
    while (env[i] != NULL)
        i++;
    if (parse->tab_arg[1] == NULL)
    {
        while (k < i - 1)
        {
            ft_putstr_fd(env[k++], 1);
            write(1, "\n", 1);
        }
    }
    while (parse->tab_arg[j] != NULL)
    {
        if (ft_strchr(parse->tab_arg[j], '='))
        {
            str = ft_split(parse->tab_arg[j], '=');
            if(getenv(str[0]))
            {
                k = i - 1;
                while (ft_var(str[0], env[k]))
                    k--;
                env[k] = parse->tab_arg[j];
            }
            else
            {
                env[i] = env[i - 1];
                env[i - 1] = parse->tab_arg[j];
                i++;
            }
        }
        ft_free_tab(str);
        j++;
        
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
    i--;
    save_i = i;
    while (parse->tab_arg[j] != NULL)
    {   
        i = save_i;
        while (i > -1)
        {
            str = ft_split(env[i], '=');
            if (!ft_strcmp(parse->tab_arg[j], str[0]))
            {
                while (i < save_i)
                {
                    env[i] = env[i + 1];
                    i++;
                }
                break;
            }
            i--;
            ft_free_tab(str);
        }
        j++;
        save_i--;
        env[i] = NULL;    
    }
}

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
            ft_putstr_fd(ft_itoa(exit_status), 1);
        else
            ft_putstr_fd(parse->tab_arg[i], 1);
        write(1, " ", 1);
        i++;
    }
    if (parse->tab_arg[1] == NULL || ft_strcmp(parse->tab_arg[1], "-n"))
        write(1, "\n", 1);
}

char *ft_pwd(t_parse *parse)
{
    char *str;

    str = malloc(sizeof(char) * PATH_MAX + 1);
    str = getcwd(str, PATH_MAX);
    return(str);
}

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
    chdir(path);
    getcwd(pwd, PATH_MAX);
    ft_update_env(pwd, env, 0);
    free(path);
}

char *ft_var_env(char *line)
{
    t_counter count;
    char *var;
    char *str;

    count.i = 0;
    count.j = 0;
    count.k = 0;
    str = malloc(sizeof(char) * ft_strlen(line) + PATH_MAX + 1);
    str[0] = '\0';
    while (line[count.i])
    {
        if (line[count.i] == '$')
        {
            var = malloc(sizeof(char) * PATH_MAX + 1);
            ft_bzero(var, ft_strlen(var));
            count.i++;
            count.j = 0;
            while (line[count.i] && line[count.i] != ' ' &&  line[count.i] != '$')
            {
                var[count.j++] = line[count.i++];
            }
            var[count.j] = '\0';
            printf("var: %s\n", var);
            if (getenv(var))
            {
                ft_strcat(str, getenv(var));
                count.k += ft_strlen(getenv(var));
            }
            free(var);
        }
        else
            str[count.k++] = line[count.i++];

    }
    str[count.k] = '\0';
    //printf("str: %s\n", str);
    return (str);  
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

int ft_is_quotes(char c)
{
    if (c == '"' || c == 39)
        return (1);
    return (0);
}

int ft_closed_quotes(char *str, int index)
{
    char quotes;

    quotes = str[index];
    index++;
    while (str[index])
    {
        if (str[index] == quotes)
            return (1);
        index++;
    }
    return (0);
}

void ft_quotes(t_parse *parse)
{
    t_counter count;
    char *str;

    count.i = 0;
    count.k = 0;
    parse->tab_simple_quotes = malloc(sizeof(char) * 500);
    while (parse->tab_arg[count.i] != NULL)
    {
        str = malloc(sizeof(char) * ft_strlen(parse->tab_arg[count.i]) + 1);
        count.j = 0;
        count.l = 0;
        while (parse->tab_arg[count.i][count.j])
        {
             if (ft_is_quotes(parse->tab_arg[count.i][count.j]) && ft_closed_quotes(parse->tab_arg[count.i], count.j))
             {
                if (parse->tab_arg[count.i][count.j] == 39)
                    parse->tab_simple_quotes[count.k++] = '1';
                else
                    parse->tab_simple_quotes[count.k++] = '0';
                count.j++;
                while (!ft_is_quotes(parse->tab_arg[count.i][count.j]) && parse->tab_arg[count.i][count.j])
                    str[count.l++] = parse->tab_arg[count.i][count.j++];
             }
             else
                str[count.l++] = parse->tab_arg[count.i][count.j];
             count.j++;
        }
        str[count.l] = '\0';
        parse->tab_simple_quotes[count.k] = '\0';
        printf("%s\n", parse->tab_simple_quotes);
        free(parse->tab_arg[count.i]);
        parse->tab_arg[count.i] = ft_strdup(str);
        free(str);
        count.i++;
    }
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
            parse->tab_arg[j] = ft_var_env(str);
        }
        j++;
    }
}

//value of exit status "$?"
//signals
//redirections and pipes
int main(int ac, char **ar, char **env)
{
    t_parse parse;
    int i;
    int j;
    int status;
    char *cmd;
    
    while(1)
    {   
        i = 0;
        cmd = readline("my_prompt>");
        add_history(cmd);
        parse.tab_cmd = ft_split(cmd, '|');
        parse.cont_env = getenv("PATH");
        parse.tab_path = ft_split(parse.cont_env, ':');
        while (parse.tab_cmd[i] != NULL)
        {
            parse.tab_arg = ft_split(parse.tab_cmd[i], ' ');
            ft_quotes(&parse);
            /*int k = 0;
            while (parse.tab_arg[k] != NULL)
                printf("arg: %s\n", parse.tab_arg[k++]);*/
            if (parse.tab_arg[0][0] != '$')
                ft_lowercase(&parse);
            j = 0;
            ft_set_env(&parse);
            if (!ft_strcmp(parse.tab_arg[0], "exit"))
            {
                ft_free(&parse);
                exit(0);
            }
            if (!ft_strcmp(parse.tab_arg[0], "export"))
                ft_export(&parse, env);
            else if (!ft_strcmp(parse.tab_arg[0], "unset"))
                ft_unset(&parse, env);
            else if (!ft_strcmp(parse.tab_arg[0], "env"))
                ft_env(env);
            else if (!ft_strcmp(parse.tab_arg[0], "echo"))
                ft_echo(&parse);
            else if (!ft_strcmp(parse.tab_arg[0], "pwd"))
            {
                ft_putstr_fd(ft_pwd(&parse), 1);
                write(1, "\n", 1);
            }
            else if (!ft_strcmp(parse.tab_arg[0], "cd"))
                ft_cd(&parse, env);
            else
            {
                if (!ft_strcmp(parse.tab_arg[0],"cat"))
                    ft_cat(&parse);
                parse.tab_arg[0] = add_cmd_to_path(parse.tab_arg[0], parse.tab_path);
                if(fork() == 0)
                {
                    exit_status = execve(parse.tab_arg[0], parse.tab_arg, env);
                    if(exit_status == -1)
                        exit(0);
                }
            }
            i++;
            wait(&status);
        }
        ft_free(&parse);
    }
}