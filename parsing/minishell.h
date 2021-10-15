#ifndef MINISHELL_H
#define MINISHELL_H

#include "./get_next_line/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct s_utils {
    int i;
    int j;
    int k;
    int cpt;
    char str[4];
}               t_utils;

char	**ft_split(char *str);
void ft_putstr(char *str);
int	ft_strcmp(char *s1, char *s2);

#endif