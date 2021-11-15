#include "minishell.h"

t_signals g_sig;

int main(int ac, char **ar, char **env)
{
    t_parse parse;
    int i;
    int j;
    int status;
    char *cmd;
    char **tab_str;
    int cmd_found;
    int s;
    
    g_exit_status = 0;
    g_pid = 0;
    while(1)
    {   
        i = 0;
        signal(SIGQUIT, sig_quit);
        signal(SIGINT, sig_int);
        cmd = readline("my_prompt>");
        add_history(cmd);
        parse.tab_cmd = ft_split_custom(cmd, '|', &parse);
        //printf("fndshfds\n");
        parse.cont_env = getenv("PATH");
        parse.tab_path = ft_split_custom(parse.cont_env, ':', &parse);
        while (parse.tab_cmd[i] != NULL)
        {
            parse.tab_arg = ft_split_custom(parse.tab_cmd[i], ' ', &parse);
            tab_str = ft_unsplit(&parse);
            ft_edit_tab_arg(&parse, tab_str);
            if (parse.tab_arg[1] != NULL && ft_strcmp(parse.tab_arg[1], "$?"))
                ft_set_env(&parse);
            ft_quotes(&parse);
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
                cmd_found = 1;
                parse.tab_arg[0] = add_cmd_to_path(parse.tab_arg[0], parse.tab_path);
                g_pid = fork();
                if(g_pid == 0)
                {
                    if(!execve(parse.tab_arg[0], parse.tab_arg, env))
                        cmd_found = 0;
                    printf("minishell: %s: command not found\n", parse.tab_arg[0]);
                    exit(127);
                }
                wait(&status);
                g_exit_status = WEXITSTATUS(status);
            }
            i++;
            ft_free_tab_arg(&parse);
        }
        ft_free(&parse);
    }
}