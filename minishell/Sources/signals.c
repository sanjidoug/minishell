#include "../minishell.h"


void sig_int()
{
    g_exit_status = 200;
    ft_putstr_fd("\n", 1);
	//ft_putstr_fd("my_prompt>", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    signal(SIGINT, sig_int2);
}
void sig_int2()
{
    ft_putstr_fd("\n", 1);
    //ft_putstr_fd("my_prompt>", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void sig_quit(int nb)
{
    g_exit_status = 200;
    ft_putstr_fd("  \b\b", 1);
    //write(1, "\0", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    signal(SIGINT, sig_int2);
    signal(SIGQUIT, sig_quit2);
}

void sig_quit2(int nb)
{
    //ft_putstr_fd("\b\b  \b\b", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}