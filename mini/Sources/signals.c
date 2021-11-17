#include "../minishell.h"


void sig_int()
{
    struct termios attributes;
    g_exit_status = 200;
    
    tcgetattr(STDIN_FILENO, &saved);
    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag = ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
    ft_putstr_fd("\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void sigint_fork()
{
    write(0, (char *)EOF, 1);
}