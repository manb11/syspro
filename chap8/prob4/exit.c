#include <stdio.h>
#include <stdlib.h>

static void exit_handler1(void), exit_handler2(void);

int main(void)
{
    if (atexit(exit_handler1) !=0)
        perror("exit_handler1 not registor");
    if (atexit(exit_handler2) !=0)
        perror("exit_handler2 not registor");
    printf("main END \n");
    exit(0);
}

static void exit_handler1(void)
{
    printf("num1 exit processor\n");
}

static void exit_handler2(void)
{
    printf("num2 exit processor\n");
}
