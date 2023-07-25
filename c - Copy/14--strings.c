#include <stdio.h>
#include <string.h>
#define N 23
#define M 10

int main() {
    // Write C code here
    char string[N];
    printf("grapse kati: ");
    scanf("%s",string);
    //h me gets(string)

    //strlen
    printf("-to mhkos ths einai: %d grammata\n",strlen(string));

    //strcpy
    char string2[N];
    strcpy(string2,string);
    printf("-to string2 einai %s\n",string2);

    //strcat
    strcat(string2,string);
    // to string2 ginetai string2+string kai to string paramenei opos einai
    printf("-to string2 einai pleon %s kai to string einai %s\n",string2,string);

    //strcmp
    int x;
    x = strcmp(string2,string);
    //dinei x<0 an string2<string alphabhtika
    //dinei x=0 an string2=string alphabhtika
    //dinei x>0 an string2>string alphabhtika
    printf("%d",x);

    //strtok
	char str[N], *p;
    char pin[M][N];
    int l=0;

	printf("\nDwse ti simvoloseira: ");
    getchar();
	gets(str);
	p=strtok(str," ,.");
	while(p!=NULL)
	{
		//printf("%s\n",p);
		strcpy(pin[l],p);
		p=strtok(NULL," ,.");
		l++;
	}


	int i;
	for(i=0;i<l;i++){
        printf("%s\n",pin[i]);
    }
    return 0;
}