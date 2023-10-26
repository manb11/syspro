#include <stdio.h> 
#include "db.dat"
int main(int argc, char* argv[]) 
{ 
   struct coffe rec;
   FILE *fp;
   if (argc != 2) { 
      fprintf(stderr, "How to use: %s FileName\n", argv[0]);
      return 1; 
   }
   if ((fp = fopen(argv[1], "rb")) == NULL ) {
      fprintf(stderr, "Error Open File\n");
      return 2;
   }
   printf("%1s %6s %6s %6s %6s\n", "id", "name", "category", "exppired data", "stock");
   while (fread(&rec, sizeof(rec), 1, fp) > 0) 
      if (rec.id != 0)
         printf("%1d %6s %6s %6d %6d\n", rec.id,  rec.name,  rec.category, rec.expired, rec.stock);
   
   fclose(fp);
   return 0;
}
