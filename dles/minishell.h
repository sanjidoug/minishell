#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <signal.h>

int g_exit_status;
int g_pid;

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

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
    char *str_dollar;
}               t_parse;

typedef struct s_utils {
    int save_j;
    int save_i;
    int start;
    int end;
    int nb_spaces;
    int cl_quotes;
}               t_utils;

typedef struct s_counter {
    int i;
    int j;
    int k;
    int l;
    int m;
}              t_counter;

typedef struct s_signals {
    int sigint;
    int sigquit;
    int exit_status;
}               t_signals;

char	**ft_split_custom(char const *s, char c, t_parse *parse);
void ft_putstr_fd(char *str, int fd);
int	ft_strcmp(char *s1, char *s2);
char *ft_strcat(char *dest, char *src);
char *ft_strcat_cd(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_itoa(int nb);
int ft_isdigit(char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
void	ft_bzero(void *b, int n);
int	ft_atoi(const char *str);
char *ft_substr(char const *s, unsigned int start, int len);
int ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_path(char const *s1, char const *s2);
int     ft_closed_quotes(char *str, int index);
int     ft_is_quotes(char c);
void ft_check_error_exit(t_parse *parse);
void ft_check_error_ex_un(t_parse *parse);
int ft_nb_arg(char **tab_arg);
char **ft_unsplit(t_parse *parse);
int ft_check_quotes(t_parse *parse, int i);
void ft_edit_tab_arg(t_parse *parse, char **tab_str);
void ft_quotes(t_parse *parse);
int ft_nb_spaces(char *str);
void ft_lowercase(t_parse *parse);
int ft_nb_arg(char **tab_arg);
char *ft_var_env(char *line, int index);
void ft_set_env(t_parse *parse);
int ft_var(char *vr_env, char* line);
void ft_env(char **env);
void ft_echo(t_parse *parse);
char *ft_pwd(t_parse *parse);
void ft_cd(t_parse *parse, char **env);
void ft_export(t_parse *parse, char **env);
void ft_unset(t_parse *parse, char **env);
void ft_update_env(char *pwd, char **env, int oldpwd);
void ft_free(t_parse *parse);
void ft_free_tab(char **tab);
void ft_free_tab_arg(t_parse *parse);
char *add_cmd_to_path(char *cmd, char **tab_path);
void sig_int();
void sig_quit2();
void sig_quit();
void sig_int2();

#endif