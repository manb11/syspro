#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( ) 
{
   printf("parent process start\n");
   if (fork( ) == 0) {
      execl("/bin/echo", "echo", "hello", NULL);
      fprintf(stderr,"ÏFisrt fail"); 
      exit(1);
   }
   
   if (fork( ) == 0) {
      execl("/bin/date", "date", NULL);
      fprintf(stderr,"Second fail"); 
      exit(2);
  }

   if (fork( ) == 0) {
      execl("/bin/ls","ls", "-l", NULL);
      fprintf(stderr,"Third fial"); 
      exit(3);
   }
   printf("parent process end \n");
}


