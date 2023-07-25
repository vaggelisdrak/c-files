#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define M 50
#define L 50

typedef struct node {
    char * string;
    struct node* next;
} Node;


typedef Node LIST_NODE; /* Sinwnimo tou komvou listas */
typedef Node *T; /* Sinwnimo tou deikti komvou */

void LL_init(T *head);
int LL_insert_start(T *head,char * str);
int LL_insert_after(T p,char * str);
int LL_insert_in_pos(T *head,int *pos,char * str);
void LL_print(T head);
void s(T x, int * chars);

void LL_reverse(T *head);
int LL_insert(T*head,char * str);
int LL_delete(T*head,char *s);
void SortLinkedList(T *head);
void swap(struct node *a, struct node *b);

int main(){
    T list;

    LL_init(&list);

    FILE *fp;
    char pin[M][L];

    int i=0;
    int j;
    fp = fopen("words.txt","r");
    if(!fp){
        exit(0);
    }

    while(fscanf(fp, "%s", pin[i])!=EOF)
	{
        i++;
    }
    fclose(fp);
    for(j=0;j<=i;j++){
        //strtok
        char *p;
        int l=0;
        p=strtok(pin[j]," ,.!'");
        while(p!=NULL)
        {
            //printf("%s\n",p);
            strcpy(pin[j],p);
            p=strtok(NULL," ,.");
            l++;
        }
    }

    for(j=0;j<i;j++){
        if(j==0){
            LL_insert_start(&list,pin[j]);
        }
        else{
            LL_insert(&list,pin[j]);
        }
        LL_print(list);
        printf("\n");
    }

    LL_reverse(&list);
    LL_print(list);

    printf("\n\n");
    SortLinkedList(&list);
    LL_print(list);

    int chars;
    s(list, &chars);
    printf("\ntotal chars: %d\n", chars);
    return 1;
}

/* LL_init(): arxikopoiei tin lista */
void LL_init(T *head){
	*head=NULL;
}

/* LL_insert_start(): Eisagei to stoixeio x
			stin arxi tis listas - dexia apo to head*/
int LL_insert_start(T *head,char * str){
	T newnode;

	newnode=(LIST_NODE *)malloc(sizeof(LIST_NODE));
	newnode->string = malloc(sizeof(char) * (strlen(str)+1));
	if (!newnode)
	{
		printf("Adynamia desmeusis mnimis");
		return FALSE;
	}
	newnode->string=str;
	newnode->next=*head;
	*head=newnode;
	return TRUE;
}

/* LL_insert_after(): Eisagei to stoixeio x
			meta to stoixeio pou deixnei o p */
int LL_insert_after(T p,char * str){
	T newnode;

	newnode=(LIST_NODE *)malloc(sizeof(LIST_NODE));
	newnode->string = malloc(sizeof(char) * (strlen(str)+1));
	if (!newnode)
	{
		printf("Adynamia desmeusis mnimis");
		return FALSE;
	}
	newnode->string=str;
	newnode->next=p->next;
	p->next=newnode;
	return TRUE;
}

/* LL_print(): Typwnei ta periexomena mias
				syndedemenis listas	 */

void LL_print(T head){
	T current;

	current=head;
	while(current!=NULL)
	{
		//printf("O/H %s exei bathmo %d\n",current->data.name,current->data.grade);
		printf("%s\n",current->string);
		current=current->next;
	}
	//printf(".");
}


/* Function to reverse the linked list */
void LL_reverse(T *head){
    T prev   = NULL;
    T current = *head;
    T next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

int LL_insert(T*head,char * str){//taxinomhsh enos komvou me alphabhtikh seira
    T current;
    T prev;

    if(*head==NULL){
        return LL_insert_after(head,str);
    }
    else{
        current = *head;
        prev = current;
        while(current!=NULL){
            if(strcmp(current->string,str)>0){
                if(current == *head){
                    return LL_insert_start(head,str);
                }
                else{
                    return LL_insert_after(prev,str);
                }
            }
            prev = current;
            current = current->next;
        }
        //an den exei ginei eisagogh epeidh einai teleytiao alphabhtika sth lista
        return LL_insert_after(prev,str);
    }
}

int LL_insert_in_pos(T *head,int *pos,char *str){
    T current;
    int i=1;
    T prev;

    if(*head==NULL){
        return LL_insert_after(head,str);
    }
    else{
        current = *head;
        prev = current;
        while(current!=NULL){
            if(i==(pos)){
                if(current == *head){
                    return LL_insert_start(head,str);
                }
                else{
                    return LL_insert_after(prev,str);
                }
            }
            prev = current;
            current = current->next;
            i++;
        }
        //an den exei ginei eisagogh epeidh einai teleytiao alphabhtika sth lista
        return LL_insert_after(prev,str);
    }
}

void SortLinkedList(T *head){
    //void bubbleSort(struct Node *start)
    int swapped, i;
    T current;
    T lptr = NULL;

    /* Checking for empty list */
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        current = *head;

        while (current->next != lptr)
        {
            if (strcmp(current->string , current->next->string)>0)
            {
                swap(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        lptr = current;
    }
    while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b)
{
    char *temp;
    temp = a->string;
    a->string = b->string;
    b->string = temp;
}

void s (T x , int * chars) {
    if (x==NULL)  return ;
    *chars += strlen(x->string);
    s(x->next, chars);
    return ;
}
