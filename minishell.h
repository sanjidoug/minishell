#ifndef MINISHELL_H
#define MINISHELL_H

#include "./get_next_line/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_parse {
    char **tab_arg;
    char **tab_cmd;
    char *cont_env;
    char **tab_path;
    char *path;
}               t_parse;

char			**ft_split(const char *str, char c);
void ft_putstr(char *str);
int	ft_strcmp(char *s1, char *s2);
char *ft_strcat(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_strjoin_path(char const *s1, char const *s2);

#endif