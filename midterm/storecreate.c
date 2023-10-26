#include <stdio.h> 
#include <stdlib.h>
#include "db.dat"

int main(int argc, char* argv[])  
{ 
	struct coffe rec;
   FILE *fp;

   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n",argv[0]);
      exit(1); 
   }

   fp = fopen(argv[1], "wb");
   printf("%-2s %-7s %-6s %-6s %-6s\n", "id", "name", "category", "expired data","stock"); 
   while (scanf("%d %s %s %d %d", &rec.id, rec.name, rec.category, 
			   &rec.expired, &rec.stock) == 5) 
	fwrite(&rec, sizeof(rec),2, fp);
   fclose(fp);
   exit(0);
} 

