#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int child, pid, fd, status;

    pid = fork( );
  if (pid == 0) {
      fd = open(argv[1],O_CREAT|
             O_TRUNC| O_WRONLY, 0600);
      dup2(fd, 1);   // 파일을 표준출력에 복제 
      close(fd);
      execvp(argv[2], &argv[2]);
      fprintf(stderr, "%s: unexecute \n",argv[1]);
    } else {
       child = wait(&status);
       printf("[%d] child process %d end \n",     
               getpid(), child);
    }
 }


