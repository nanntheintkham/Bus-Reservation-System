#include<stdio.h>

int main(){
 FILE *fp = fopen("reservedList.txt", "w");
 fprintf(fp, "SuaJ\t\t5\t\t1");
 fflush(fp);
 fclose(fp);
 return 0;
}

