#include "./minishell.h"


void sig_int()
{
    ft_putstr_fd("\b\b\b\b\n", 1);
	ft_putstr_fd("my_prompt>", 1);
    rl_on_new_line();
    //rl_redisplay();
    signal(SIGINT, sig_int2);
}
void sig_int2()
{
    ft_putstr_fd("\b\b  \b\b\n", 1);
    ft_putstr_fd("my_prompt>", 1);
    rl_on_new_line();
    //rl_redisplay();
}

void sig_quit(int nb)
{
    ft_putstr_fd("\b\b\b\b", 1);
    rl_on_new_line();
    //rl_redisplay();
    signal(SIGQUIT, sig_quit2);
}


void sig_quit2(int nb)
{
    ft_putstr_fd("\b\b  \b\b", 1);
    rl_on_new_line();
    //rl_redisplay();
}