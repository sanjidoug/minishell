#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

unsigned int exit_status;

typedef struct s_parse {
    char **tab_arg;
    char **tab_cmd;
    char *cont_env;
    char **tab_path;
    char *path;
    char quotes;
    char *tab_simple_quotes;
    int dollar;
    int *tab_spaces;
}               t_parse;

typedef struct s_counter {
    int i;
    int j;
    int k;
    int l;
    int m;
}              t_counter;

char	**ft_split_custom(char const *s, char c, t_parse *parse);
void ft_putstr_fd(char *str, int fd);
int	ft_strcmp(char *s1, char *s2);
char *ft_strcat(char *dest, char *src);
char *ft_strcat_cd(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_itoa(int nb);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
void	ft_bzero(void *b, int n);
char *ft_substr(char const *s, unsigned int start, int len);
int ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_path(char const *s1, char const *s2);
int     ft_closed_quotes(char *str, int index);
int     ft_is_quotes(char c);

#endif