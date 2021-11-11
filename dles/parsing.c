#include "minishell.h"

int main(int ac, char **ar, char **env)
{
    t_parse parse;
    int i;
    int j;
    int status;
    char *cmd;
    char **tab_str;
    
    g_exit_status = 0;
    while(1)
    {   
        i = 0;
        cmd = readline("my_prompt>");
        add_history(cmd);
        parse.tab_cmd = ft_split_custom(cmd, '|', &parse);
        parse.cont_env = getenv("PATH");
        parse.tab_path = ft_split_custom(parse.cont_env, ':', &parse);
        while (parse.tab_cmd[i] != NULL)
        {
            if (!ft_closed_quotes(parse.tab_arg[0], 0))
            {
                parse.tab_arg = ft_split_custom(parse.tab_cmd[i], ' ', &parse);
                if (parse.tab_arg[0][0] != '"')
                {
                    tab_str = ft_unsplit(&parse);
                    ft_edit_tab_arg(&parse, tab_str);
                }
                ft_quotes(&parse);
            }
            else
                
            int k = 0;
            while (parse.tab_arg[k] != NULL)
                printf("%s\n", parse.tab_arg[k++]);
            if (parse.tab_arg[0][0] != '$')
                ft_lowercase(&parse);
            if (parse.tab_arg[1] != NULL && ft_strcmp(parse.tab_arg[1], "$?"))
                ft_set_env(&parse);
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
                parse.tab_arg[0] = add_cmd_to_path(parse.tab_arg[0], parse.tab_path);
                if(fork() == 0)
                {
                    execve(parse.tab_arg[0], parse.tab_arg, env);
                    exit(0);
                }
                wait(&status);
                g_exit_status = WEXITSTATUS(status);
            }
            i++;
        }
        ft_free(&parse);
    }
}