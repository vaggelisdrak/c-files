#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


struct ELEM{
    char name[80];
    int grade;
};
typedef struct ELEM elem;          /* typos dedomenwn listas */

struct node{			   /* Typos komvou listas */
   elem data; 			   /* dedomena */
   struct node *next;      /* epomenos */
};

typedef struct node LIST_NODE; /* Sinwnimo tou komvou listas */
typedef struct node *LIST_PTR; /* Sinwnimo tou deikti komvou */

void LL_init(LIST_PTR *head);
int LL_empty(LIST_PTR head);
elem LL_data(LIST_PTR p);
int LL_insert_start(LIST_PTR *head,elem x);
int LL_insert_after(LIST_PTR p,elem x);
int LL_delete_start(LIST_PTR *head, elem *x);
int LL_delete_after(LIST_PTR prev, elem *x);
int LL_insert_in_pos(LIST_PTR *head,int *pos,elem x);
void LL_print(LIST_PTR head);
void LL_destroy(LIST_PTR *head);


void LL_reverse(LIST_PTR *head);
int LL_insert(LIST_PTR*head,elem x);
int LL_delete(LIST_PTR*head,char *s);
int LL_mesosoros(LIST_PTR head);
int LL_pass(LIST_PTR head);
void SortLinkedList(LIST_PTR *head);
void swap(struct node *a, struct node *b);

int main(){
    LIST_PTR list;
    elem student;

    LL_init(&list);


    strcpy(student.name,"myga");
    student.grade = 7;
    LL_insert_start(&list,student);

    strcpy(student.name,"mygoxesma");
    student.grade = 1;
    LL_insert_start(&list,student);

    strcpy(student.name,"bosxari");
    student.grade = 4;
    LL_insert_start(&list,student);

    strcpy(student.name,"kounoupi");
    student.grade = 5;
    LL_insert_start(&list,student);

    strcpy(student.name,"avaggelis");
    student.grade = 10;
    LL_insert_start(&list,student);

    strcpy(student.name,"rounoupomyga");
    student.grade = 5;
    LL_insert(&list,student);

    //LL_reverse(&list);
    LL_delete(&list,"myga");
    LL_print(list);
    LL_mesosoros(list);
    LL_pass(list);
    printf("\n");

    strcpy(student.name,"mosxaromygaa");
    student.grade = 2;
    LL_insert_in_pos(&list,3,student);
    LL_print(list);

    printf("\n\n");
    SortLinkedList(&list);
    LL_print(list);
    LL_destroy(&list);
    return 1;
}

/* LL_init(): arxikopoiei tin lista */
void LL_init(LIST_PTR *head){
	*head=NULL;
}

/* LL_empty(): epistrefei TRUE/FALSE
 *          analoga me to an i lista einai adeia */
int LL_empty(LIST_PTR head){
	return head == NULL;
}

/* LL_data(): epistrefei ta dedomena tou komvou
			  pou deixnei o deiktis p */
elem LL_data(LIST_PTR p){
	return p->data;
}

/* LL_insert_start(): Eisagei to stoixeio x
			stin arxi tis listas - dexia apo to head*/
int LL_insert_start(LIST_PTR *head,elem x){
	LIST_PTR newnode;

	newnode=(LIST_NODE *)malloc(sizeof(LIST_NODE));
	if (!newnode)
	{
		printf("Adynamia desmeusis mnimis");
		return FALSE;
	}
	newnode->data=x;
	newnode->next=*head;
	*head=newnode;
	return TRUE;
}

/* LL_insert_after(): Eisagei to stoixeio x
			meta to stoixeio pou deixnei o p */
int LL_insert_after(LIST_PTR p,elem x){
	LIST_PTR newnode;

	newnode=(LIST_NODE *)malloc(sizeof(LIST_NODE));
	if (!newnode)
	{
		printf("Adynamia desmeusis mnimis");
		return FALSE;
	}
	newnode->data=x;

	newnode->next=p->next;
	p->next=newnode;
	return TRUE;
}

/* LL_delete_start(): Diagrafei ton komvo poy deixnei
	i kefali tis listas */
int LL_delete_start(LIST_PTR *head, elem *x){
	LIST_PTR current;

	if (*head==NULL)
		return FALSE;

	current=*head;
	*x=current->data;

	(*head)=(*head)->next;
	free(current);
	return TRUE;
}

/* LL_delete_after(): Diagrafei ton epomeno tou
				komvou poy deixnei o prev */
int LL_delete_after(LIST_PTR prev, elem *x){
	LIST_PTR current;

	if (prev->next==NULL)
		return FALSE;

	current=prev->next;
	*x=current->data;

	prev->next=current->next;
	free(current);
	return TRUE;
}

/* LL_print(): Typwnei ta periexomena mias
				syndedemenis listas	 */

void LL_print(LIST_PTR head){
	LIST_PTR current;

	current=head;
	while(current!=NULL)
	{
		//printf("O/H %s exei bathmo %d\n",current->data.name,current->data.grade);
		printf("[ %s , %d ]->",current->data.name,current->data.grade);
		current=current->next;
	}
	printf(".");
}

/* LL_destroy(): Apodesmeyei to xwro poy exei
				desmeusei i lista	 */

void LL_destroy(LIST_PTR *head){
	LIST_PTR ptr;

	while (*head!=NULL)
	{
		ptr=*head;
		*head=(*head)->next;
		free(ptr);
	}
}

/* Function to reverse the linked list */
void LL_reverse(LIST_PTR *head){
    LIST_PTR prev   = NULL;
    LIST_PTR current = *head;
    LIST_PTR next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}


int LL_insert(LIST_PTR*head,elem x){//taxinomhsh enos komvou me alphabhtikh seira
    LIST_PTR current;
    LIST_PTR prev;

    if(*head==NULL){
        return LL_insert_after(head,x);
    }
    else{
        current = *head;
        prev = current;
        while(current!=NULL){
            if(strcmp(current->data.name,x.name)>0){
                if(current == *head){
                    return LL_insert_start(head,x);
                }
                else{
                    return LL_insert_after(prev,x);
                }
            }
            prev = current;
            current = current->next;
        }
        //an den exei ginei eisagogh epeidh einai teleytiao alphabhtika sth lista
        return LL_insert_after(prev,x);
    }
}

int LL_delete(LIST_PTR*head,char *s){
    LIST_PTR current;
    LIST_PTR prev;

    elem temp;

    if(*head==NULL){
        return 0;
    }
    else{
        current = *head;
        prev = current;
        while(current!=NULL){
            if(strcmp(current->data.name,s)==0){
                if(current == *head){
                    return LL_delete_start(head,&temp);
                }
                else{
                    return LL_delete_after(prev,&temp);
                }
            }
            prev = current;
            current = current->next;
        }
        //an den exei ginei eisagogh epeidh einai teleytiao alphabhtika sth lista
        return LL_delete_after(prev,&temp);
    }
}

int LL_insert_in_pos(LIST_PTR *head,int *pos,elem x){
    LIST_PTR current;
    int i=1;
    LIST_PTR prev;

    if(*head==NULL){
        return LL_insert_after(head,x);
    }
    else{
        current = *head;
        prev = current;
        while(current!=NULL){
            if(i==(pos)){
                if(current == *head){
                    return LL_insert_start(head,x);
                }
                else{
                    return LL_insert_after(prev,x);
                }
            }
            prev = current;
            current = current->next;
            i++;
        }
        //an den exei ginei eisagogh epeidh einai teleytiao alphabhtika sth lista
        return LL_insert_after(prev,x);
    }
}


int LL_mesosoros(LIST_PTR head){
    LIST_PTR current;
    int i;
    int sum=0;

	current=head;
	while(current!=NULL)
	{
		sum += current->data.grade;
		current=current->next;
		i++;
	}
	printf("\no mesos oros einai %.2f\n",(double)sum/i);
	return 1;
}

int LL_pass(LIST_PTR head){
    LIST_PTR current;
    int pass=0;
    int i=0;

	current=head;
	while(current!=NULL)
	{
        if(current->data.grade>=5){
            printf("o/h %s perase to mathima me %d\n",current->data.name,current->data.grade);
            pass+=1;
        }
		current=current->next;
		i++;
	}
	printf("\nOi epityxontes einai %d pososto %.2f tis ekato dld %d/%d\n",pass,(double)100*pass/i,pass,i);
	return 1;
}

void SortLinkedList(LIST_PTR *head){
    //void bubbleSort(struct Node *start)
    int swapped, i;
    LIST_PTR current;
    LIST_PTR lptr = NULL;

    /* Checking for empty list */
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        current = *head;

        while (current->next != lptr)
        {
            if (current->data.grade > current->next->data.grade)
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
    struct ELEM temp;
    temp = a->data;
    a->data = b->data;
    b->data = temp;
}
