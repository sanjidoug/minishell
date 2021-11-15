#include <signal.h>
#include <stdio.h>

void func()
{
    printf("hello\n");
}

int main()
{
    while (1)
        signal(SIGINT, func);
}