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

typedef struct s_cmd{
    char **tab_arg;
    char *cmd;
    char **redir_out;
    char **redir_in;
    int pipes;
}               t_cmd;

typedef struct s_redo{
    int fd;
    char *file;
    int append;
}               t_redo;

typedef struct s_parse {
    char **tab_arg;
    char **tab_cmd;
    char *cont_env;
    char **tab_path;
    char *path;
    int dollar;
    char *tab_simple_quotes;
    int fd[2];
    char **fout;
    int redir_out;
    int redir_in;
    //int redir;
    int fd_redir_out;
    int out;
    t_redo *redo;
    t_redo *redin;
    int cout;
}               t_parse;

typedef struct s_counter {
    int i;
    int j;
    int k;
    int l;
    int m;
}              t_counter;

char			**ft_split(const char *str, char c);
void ft_putstr_fd(char *str, int fd);
int	ft_strcmp(char *s1, char *s2);
char *ft_strcat(char *dest, char *src);
char *ft_strcat_cd(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_itoa(int nb);
char	*ft_strchr(const char *s, int c);
int ft_find_char(char *str, char c);
int ft_strlen(char *str);
char	*ft_strdup(char *src);
int ft_find_next_char(char *str, char c);
int ft_count(char *str, char c);
char	*ft_strjoin_path(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_bzero(void *b, int n);
int ft_redir_out(t_parse *parse,int index, t_redo *redo);
void ft_fd_out(t_parse *parse);
int ft_delchar(char *str, int i);
int ft_delstr(char **str, int index);
int ft_redirection(t_parse *parse);
int free_red(t_parse *parse);
void ft_redir_in(t_parse *parse,int index, t_redo *redin);
int ft_delfile(t_parse *parse, int n, int s);
void ft_fd_in(t_parse *parse);
char *ft_parse_file(char *str);
void init_count(t_counter *count);
int ft_search_redir(t_parse *parse, t_counter *count, int i);
#endif