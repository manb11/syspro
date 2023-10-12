#include <stdio.h>
#include "copy.h" 
#include <string.h>

char line[5] ;
char longest[MAXLINE] ;

int main()
{	
	int len=0 ;
	int max=0 ;


	while (fgets(line,MAXLINE,stdin) != NULL) 
	{
		len = strlen(line);

		if (len > max) {
			max = len;
			copy(line, longest);
		}
	}	
	if(max > 0)
	
		printf("%s \n", longest);
	

	return 0;
}
