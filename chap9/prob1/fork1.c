#include <stdio.h>
#include <unistd.h>
/* 자식 프로세스를 생성한다. */
int main()
{ 
   int pid;
   printf("[%d] proccess start \n", getpid());
   pid = fork();
   printf("[%d] process : return %d\n", getpid(), pid);
}


