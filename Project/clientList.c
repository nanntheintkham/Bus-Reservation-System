#include<stdio.h>

int main(){
 FILE *fp = fopen("clientList.txt", "w");
 fprintf(fp, "SuaJ\t\tSua\t\t12345\t\t02034952\t\tsjj@gmail.com\t\t\n");
 fprintf(fp, "JangYeJung\t\tYeJJ\t\t12345\t\t01023143\t\tjyj@gmail.com\t\t\n");
 fprintf(fp, "KyawtKyawtZin\t\tKkzin\t\t12345\t\t09243513\t\tkkz@gmail.com\t\t\n");
 fflush(fp);
 fclose(fp);
 return 0;
}
