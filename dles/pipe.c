#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"





int main()	
{
    int   s;
    int   i;
    char  urli[100];
    char  urlo[100];
    int   fd[2];
    if (pipe(fd) != 0)
    {
      printf("Error\n");
      exit(1);
    }
    if ( fork() == 0 )
    {
        close(fd[0]);
        write(fd[1], "urli urlo", 100);
        close(fd[1]);
        exit(0);      
    } 
    if ( fork() == 0 )
    {
        close(fd[1]);                           
        read(fd[0], &urlo, 100);    
        printf("%s\n", urlo);
        close(fd[0]);
        exit(0);
    }		 
    close(fd[0]); 
    close(fd[1]);
    printf("attente de la fin des processus!\n");
    i=wait(&s);   
    i=wait(&s);   
    printf("fin du programme\n");
    exit(0);
}





/*
tableau de pipe(1 par cmd - 1)
chaque commande sauf la derniere on creer un pipe
chaque commande sauf la 1ere on recupere le pipe
on close sortie/entree standard dans les forks correspondant
pour les redirections on creer avec open si l'ouverture echoue,
si simple on ecrit direct (EOF ?) sinon on va jusqua la fin avant (gnl)