#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"

void ft_split2(t_cmd **cmd, char *str, int sep)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    j = 0;
    while(cmd[i + 1]->cmd != NULL)
        i++;
    j = ft_strlen(cmd[i + 1]->cmd) - sep;
    cmd[i + 1]->cmd = malloc(sizeof(char) * (sep + 1));
    cmd[i]->cmd[j++] = 0;
    while(cmd[i]->cmd[j])
    {
        cmd[i + 1]->cmd[k++] = cmd[i]->cmd[j];
        cmd[i]->cmd[j++] = 0;
    }
    cmd[i + 1]->cmd[k] = 0;
}


void ft_split_quote(t_cmd **cmd, char *arg, char c)
{
    int i;
    int j;
    char **tab;

    i = 0;
    j = 0;
    cmd[0]->cmd = ft_strdup(arg);
    cmd[1]->cmd = NULL;
    while(arg[i])
    {
        if(arg[i] == '"' || arg[i] == 39)
            i += ft_find_next_char(arg + i, arg[i]);
        if(arg[i] == c)
        {
            ft_split2(cmd ,arg, ft_strlen(arg - i));
        }
        i++;
    }
}


int parse_cmd(char *arg)
{
    t_cmd *cmd;
    int i;

    i = 0;
    cmd = malloc(sizeof(t_cmd) * ft_count(arg, '|') + 2);
    ft_split_quote(&cmd, arg, '|');
    return(1);
}

int main()
{
    parse_cmd("test '|' dfdsf | fdsf");
}




/*
tableau de pipe(1 par cmd - 1)
chaque commande sauf la derniere on creer un pipe
chaque commande sauf la 1ere on recupere le pipe
on close sortie/entree standard dans les forks correspondant
pour les redirections on creer avec open si l'ouverture echoue,
si simple on ecrit direct (EOF ?) sinon on va jusqua la fin avant (gnl)*/