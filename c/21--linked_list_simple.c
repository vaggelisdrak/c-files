// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node NODE;


int main(void)
{
    NODE *head, *temp;
    int i;

    head = (NODE *)malloc(sizeof(NODE)); //allocate memory for the first node pointer called head
    temp = head; //temp node pointer 
    for (i = 0; i < 10; i++)
    {
        temp->data = i; //node's data = i
        if (i == 9) //stop the iter in last node so that we can do temp=>next = NULL 
            break;
        temp->next = (NODE *)malloc(sizeof(NODE)); //allocate memory for the next node pointer 
        temp = temp->next; //new node pointer = the next one
    }
    temp->next = NULL;

    temp = head; //init linked list
    for (i = 0; i < 10; i++)
    {
        printf("%d %d\n", temp->data, temp->next);
        temp = temp->next;
    }
    return 0;
}

