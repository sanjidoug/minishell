#include "../minishell.h"

int ft_putstr_fd(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
    return(1);
}