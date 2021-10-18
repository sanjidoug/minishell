#ifndef MINISHELL_H
#define MINISHELL_H

#include "./get_next_line/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_utils {
    char *str;
    int len_bequal;
}               t_utils;

/*typedef struct s_parse {

}*/

char			**ft_split(const char *str, char c);
void ft_putstr(char *str);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup_env(char *src, t_utils utils);
char *ft_strcat(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_strjoin_path(char const *s1, char const *s2);

#endif