#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 50

typedef struct the3 {
    int * data;
    struct the3* next;
}The3;

typedef The3 LIST_NODE; /* Sinwnimo tou komvou listas */
typedef The3 *T; /* Sinwnimo tou deikti komvou */
typedef int X;

void LL_init(T *head);
T LL_create_node(int * x);
int LL_insert_start(T *head,int * x);
void LL_print(T head);
void s(T x, int *sum);
void m(T * head);

void LL_reverse(T *head);
void SortLinkedList(T *head);
void swap(struct the3 *a, struct the3 *b);

int main(){
    T list;

    LL_init(&list);

    FILE *fp;
    int pin[M];

    int i=0;
    int j;
    fp = fopen("words.txt","r");
    if(!fp){
        exit(0);
    }

    while(fscanf(fp, "%d", &pin[i])!=EOF)
	{
	    //printf("%d",pin[i]);
        i++;
    }
    fclose(fp);

    for(j=0;j<i;j++){
        LL_insert_start(&list,pin[j]);
        SortLinkedList(&list);
        LL_reverse(&list);
        LL_print(list);
        LL_reverse(&list);
        printf("\n");
    }

    int *sum;
    sum = 0;
    s(list, &sum);
    printf("\nto auroisma einai %d\n",sum);

    int s;
    s = 0;
    m(&list);
    //printf("%d",s);
    return 1;
}

/* LL_init(): arxikopoiei tin lista */
void LL_init(T *head){
	*head=NULL;
}

/* LL_insert_start(): Eisagei to stoixeio x
			stin arxi tis listas - dexia apo to head*/
int LL_insert_start(T *head,int * x){
	T newnode;

	newnode=(LIST_NODE *)malloc(sizeof(LIST_NODE));
	newnode->data = malloc(sizeof(int));
	if (!newnode)
	{
		printf("Adynamia desmeusis mnimis");
		return 0;
	}
	newnode->data=x;
	//newnode->next=NULL;
	newnode->next=*head;
	*head=newnode;
	return 1;
}


/* LL_print(): Typwnei ta periexomena mias
				syndedemenis listas	 */

void LL_print(T head){
	T current;
	while(current!=NULL)
	{
		//printf("O/H %s exei bathmo %d\n",current->data.name,current->data.grade);
        if(current->next == NULL){
            printf("%d",current->data);
        }
        else{
            printf("%d->",current->data);
        }
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
            if((int)current->data %2 !=0 && (int)current->next->data %2==0)
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
void swap(struct the3 *a, struct the3 *b)
{
    char *temp;
    temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void s(T x , int * sum) {
    if (x==NULL)  return ;
    *sum += x->data;
    s(x->next,&sum);
    return ;
}

void m(T *head){
    //LL_insert(LIST_PTR*head,elem x){//taxinomhsh enos komvou me alphabhtikh seira
    T current;
    int i=0;
    int j=1;
    int prev;
    int med;
    current = *head;
    while(current!=NULL)
	{
	    i++;
		current=current->next;
	}
	current = *head;
	while(current!=NULL)
	{
        if(i%2!=0 && j==(i+1)/2){
            med = current->data;
            printf("%d",med);
        }
        if(i%2==0 && j==i/2){
            prev = current->data;
        }
        if(i%2==0 && j==(i/2 + 1)){
            double med;
            int l;
            l = prev+(int)current->data;
            med = (double)l/2;
            printf("%g",med);
        }
		j++;
		current = current->next;
	}
}
