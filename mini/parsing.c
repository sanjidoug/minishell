#include "./minishell.h"
#include <stdio.h>
#include <errno.h>

void ft_descriptor(t_parse *parse, char **env, int i)
{
    if (parse->redir_in != 0)
        ft_fd_in(parse);
    if (parse->redir_out != 0)
        ft_fd_out(parse);
    if(parse->tab_cmd[i + 1] != NULL)
    {
        close(parse->fd[0]);
        close(1);
        dup(parse->fd[1]);
        close(parse->fd[1]);
    }
    if(i != 0)
    {
        close(0);
        dup(parse->out);
        close(parse->out);
    }
}


void ft_prefork(t_parse *parse, char **env)
{
    if(parse->tab_arg[1] != NULL && !ft_is_question_mark(parse))
        ft_set_env(parse, env);
    ft_quotes(parse);
    if (parse->tab_arg[0][0] != '$')
        ft_lowercase(parse);
    if (!ft_strcmp(parse->tab_arg[0], "exit"))
    {
        ft_putstr_fd("exit\n", 1);
        ft_check_error_exit(parse);
        if (parse->tab_arg[1] != NULL && ft_nb_arg(parse->tab_arg) < 3)
            g_exit_status = ft_atoi(parse->tab_arg[1]);
        if (ft_nb_arg(parse->tab_arg) < 3)
        {
            ft_free(parse);
            exit(g_exit_status);
        }
        else
            exit(1);
    }
    else if (!ft_strcmp(parse->tab_arg[0], "export") && parse->tab_arg[1] != NULL)
        ft_export(parse, env);
    else if (!ft_strcmp(parse->tab_arg[0], "unset"))
        ft_unset(parse, env);
    else if (!ft_strcmp(parse->tab_arg[0], "cd"))
        ft_cd(parse, env);
}


void ft_exec(t_parse *parse, char **env)
{
    if (!ft_strcmp(parse->tab_arg[0], "export"))
        ft_export(parse, env);
    else if (!ft_strcmp(parse->tab_arg[0], "env"))
        ft_env(env);
    else if (!ft_strcmp(parse->tab_arg[0], "echo"))
        ft_echo(parse);
    else if (!ft_strcmp(parse->tab_arg[0], "pwd"))
    {
        ft_putstr_fd(ft_pwd(parse), 1);
        write(1, "\n", 1);
    }
    else if (ft_strcmp(parse->tab_arg[0], "export") && ft_strcmp(parse->tab_arg[0], "unset") && ft_strcmp(parse->tab_arg[0], "cd"))
    {
        parse->tab_arg[0] = add_cmd_to_path(parse->tab_arg[0], parse->tab_path);
        execve(parse->tab_arg[0], parse->tab_arg, env);
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(ft_strjoin(parse->tab_arg[0], ": "), 2);
        if(ft_strchr(parse->tab_arg[0], '/'))
            perror("");
        else
            ft_putstr_fd("command not found\n", 2);
        exit(127);
    }
}

void ft_fork(t_parse *parse, char **env, char **tab_str ,int i)
{
    int status;
    
    status = 0;
    pipe(parse->fd);
    parse->redir_out = 0;
    parse->redir_in  = 0;
    parse->tab_arg = ft_split_custom(parse->tab_cmd[i], ' ', parse);
    tab_str = ft_unsplit(parse);
    ft_edit_tab_arg(parse, tab_str);
    ft_free_tab(tab_str);
    ft_prefork(parse, env);
    if (ft_redirection(parse))
        exit(1);
    if(fork() == 0)
    {
        ft_descriptor(parse, env, i);
        ft_exec(parse, env);
        exit(1);
    }
    wait(&status);
    g_exit_status = WEXITSTATUS(status);
    if(!ft_strchr(parse->tab_cmd[i], '>'))
        parse->out = parse->fd[0];
    close(parse->fd[1]);
}

void ft_init_mini(t_parse *parse, char **env, char **cmd)
{
    if(!*cmd)
    {
        ft_putstr_fd("exit\n", 1);
        exit(1);
    }
    add_history(*cmd);
    parse->tab_cmd = ft_split_pipe(*cmd);
    parse->cont_env = getenv("PATH");
    parse->tab_path = ft_split(parse->cont_env, ':');
}

int main(int ac, char **ar, char **env)
{
    t_parse parse;
    int i;
    char *cmd;
    char **tab_str;
    ac = 0;
    ar = NULL;
    
    while(1)
    {   
        i = 0;
        signal(SIGINT, sig_int);
        signal(SIGQUIT, SIG_IGN);
        cmd = readline("my_prompt>");
        ft_init_mini(&parse, env, &cmd);
        while (parse.tab_cmd != NULL && parse.tab_cmd[i] != NULL && parse.tab_cmd[i][0] != 0)
        {
            ft_fork(&parse, env, tab_str, i);
            ft_free_tab(parse.tab_arg);
            free(parse.redo);
            free(parse.redin);
            i++;
        }
        ft_free_tab(parse.tab_path);
        ft_free_tab(parse.tab_cmd);
    }
}
