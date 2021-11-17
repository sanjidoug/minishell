#include "./minishell.h"
#include <stdio.h>
#include <errno.h>

int main(int ac, char **ar, char **env)
{
    t_parse parse;
    int i;
    int j;
    int status;
    int tmp_g_exit_status;
    char *cmd;
    char **tab_str;
    
    while(1)
    {   
        i = 0;
        signal(SIGINT, sig_int);
        signal(SIGQUIT, SIG_IGN);
        tmp_g_exit_status = g_exit_status;
        cmd = readline("my_prompt>");
        if(!cmd && g_exit_status != 200)
        {
            g_exit_status = tmp_g_exit_status;
            ft_putstr_fd("exit\n", 1);
            exit(0);
        }
        g_exit_status = tmp_g_exit_status;
        add_history(cmd);
        parse.tab_cmd = ft_split_pipe(cmd);
        /*i = 0;
        while(parse.tab_cmd[i] != NULL)
            printf("cmd1 = %s et =%d\n", parse.tab_cmd[i], ft_strlen(parse.tab_cmd[i++]));
        //ft_free_tab(parse.tab_cmd);*/
        //parse.tab_cmd = ft_split(cmd, '|');
        /*i = 0;
        while(parse.tab_cmd[i] != NULL)
            printf("cmd2 = %s et =%d\n", parse.tab_cmd[i], ft_strlen(parse.tab_cmd[i++]));*/
        parse.cont_env = getenv("PATH");
        parse.tab_path = ft_split_custom(parse.cont_env, ':', &parse);
        while (parse.tab_cmd != NULL && parse.tab_cmd[i] != NULL)
        {
            pipe(parse.fd);
            parse.redir_out = 0;
            parse.redir_in  = 0;
            parse.tab_arg = ft_split_custom(parse.tab_cmd[i], ' ', &parse);
            tab_str = ft_unsplit(&parse);
            /*int k = 0;
            while (tab_str[k] != NULL)
                printf("tab_str: %s\n", tab_str[k++]);*/
            ft_edit_tab_arg(&parse, tab_str);
            /*if (!parse.tab_arg)
                return (ft_free(&parse));*/
            if(parse.tab_arg[1] != NULL && !ft_is_question_mark(&parse))
                ft_set_env(&parse, env);
            ft_quotes(&parse);
            /*if(!ft_quotes(&parse))
                return (ft_free(&parse));*/
            if (parse.tab_arg[0][0] != '$')
                ft_lowercase(&parse);
            if (!ft_strcmp(parse.tab_arg[0], "exit"))
            {
                ft_putstr_fd("exit\n", 1);
                ft_check_error_exit(&parse);
                if (parse.tab_arg[1] != NULL && ft_nb_arg(parse.tab_arg) < 3)
                    g_exit_status = ft_atoi(parse.tab_arg[1]);
                if (ft_nb_arg(parse.tab_arg) < 3)
                {
                    ft_free(&parse);
                    exit(g_exit_status);
                }
                else
                    break;
            }
            else if (!ft_strcmp(parse.tab_arg[0], "export") && parse.tab_arg[1] != NULL)
                    ft_export(&parse, env);
            else if (!ft_strcmp(parse.tab_arg[0], "unset"))
                    ft_unset(&parse, env);
            else if (!ft_strcmp(parse.tab_arg[0], "cd"))
                    ft_cd(&parse, env);
            if (ft_redirection(&parse))
                break;
            if(fork() == 0)
            {
                signal(SIGINT, sigint_fork);
                if(parse.tab_cmd[i + 1] != NULL)
                {
                    close(parse.fd[0]);
                    close(1);
                    dup(parse.fd[1]);
                    close(parse.fd[1]);
                }
                if(i != 0)
                {
                    close(0);
                    dup(parse.out);
                    close(parse.out);
                }
                if (parse.redir_in != 0)
                    ft_fd_in(&parse);
                if (parse.redir_out != 0)
                    ft_fd_out(&parse);
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
                 else if (ft_strcmp(parse.tab_arg[0], "export") && ft_strcmp(parse.tab_arg[0], "unset") && ft_strcmp(parse.tab_arg[0], "cd"))
                {
                    parse.tab_arg[0] = add_cmd_to_path(parse.tab_arg[0], parse.tab_path);
                    execve(parse.tab_arg[0], parse.tab_arg, env);
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd(ft_strjoin(parse.tab_arg[0], ": "), 2);
                    if(ft_strchr(parse.tab_arg[0], '/'))
                        perror("");
                    else
                        ft_putstr_fd("command not found\n", 2);
                    exit(127);
                }
                exit(0);
            }
            i++;
            wait(&status);
            g_exit_status = WEXITSTATUS(status);
            if(!ft_strchr(parse.tab_cmd[i - 1], '>'))
                parse.out = parse.fd[0];
            /*else
                parse.out = open(parse.redo[0].file, O_RDONLY);*/
            close(parse.fd[1]);
            ft_free_tab(parse.tab_arg);
        }
        ft_free_tab(parse.tab_path);
        ft_free_tab(parse.tab_cmd);
    }
}