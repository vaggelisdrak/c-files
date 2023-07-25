#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 150
#define L 150


int main(){
    FILE *fp;
    char pin[M][L];

    fp = fopen("text.txt","w");
    if(!fp){
        exit(0);
    }
    fprintf(fp,"hello my name is ahkmal");
    fclose(fp);

    fp = fopen("text.txt","a");
    fprintf(fp,"\n,from it tech support!");
    fclose(fp);

    //char word[M];
    int i=0;
    int j;
    fp = fopen("text.txt","r");
    //while((ch = fgetc(fp)) != EOF){
        //printf("%c", ch);

    while(fscanf(fp, "%s", pin[i])!=EOF)
	{
	    //printf("%s\n",pin[i]);
        i++;
    }
    fclose(fp);
    
    for(j=0;j<=i;j++){
        //strtok
        char *p;
        //int l=0;
        p=strtok(pin[j]," ,.!'");
        while(p!=NULL)
        {
            //printf("%s\n",p);
            strcpy(pin[j],p);
            p=strtok(NULL," ,.");
            //l++;
        }
    }

    for(j=0;j<=i;j++){
        printf("%s\n",pin[j]);
    }
    return 0;
}