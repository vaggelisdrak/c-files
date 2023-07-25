// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node
{
    int AM;
    char *surname;
    struct node *next;
} STUDENT;

STUDENT * create_student_node(int AM, char *surname);
void printlist(STUDENT *nd);
STUDENT * getStudent(STUDENT *nd, int AM);
void deleteStudent(STUDENT **head, int AM);

int main(void)
{
    STUDENT *head,*tmp;
    head=create_student_node(0, "s1");
    tmp=head;

    int i;
    for(i=1;i<100;i++){
        tmp->next = create_student_node(i, "s");
        tmp = tmp->next;
    }

    deleteStudent(&head, 3);
    printlist(head);

    if (getStudent(head, 50)) {
        printf("student id: %d \n", getStudent(head, 50)->AM);
    }

    return 0;
}

STUDENT * create_student_node(int AM, char *surname)// create new node
{
    STUDENT *node;
    node = (STUDENT *)malloc(sizeof(STUDENT));
    if (!node)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {
        node->AM = AM;
        node->surname = (char *)calloc(strlen(surname) + 1, sizeof(char));
        strcpy(node->surname, surname);
        node->next = NULL;
        return node;
    }
}

void printlist(STUDENT *nd){ //print nodes
    STUDENT * iter;
    for(iter=nd;iter!=NULL;iter=iter->next){
        printf("student id: %d \n", iter->AM);
    }
}

STUDENT *getStudent(STUDENT *nd, int AM) //search node in linked list
{
    STUDENT *iter;
    for (iter = nd; iter != NULL; iter = iter->next)
    {
        if (iter->AM == AM)
            return iter;
    }
    return NULL;
}

void deleteStudent(STUDENT **head, int AM) //delete node from linked list
{
    STUDENT *student = NULL;
    student = getStudent(*head, AM);

    if (*head == student)
        *head = student->next; //thelo *head oste na mhn allazei mono topika o deikths,alla kai exo apo thn syn.dld passed by reference oxi by value gia ton deikth head
    else
    {
        STUDENT *iter = *head;
        for (; iter != NULL && iter->next != student;iter = iter->next);//ftano ston komvo prin apo ayton stou student - find previous node
        if (iter != NULL)
            iter->next = student->next; //allazo ton deikth toy komvoy oste na mhn deixnei ton student komvo alla ton epomeno (ayton poy deixnei o student)
    }
    free(student->surname);//adeiazo thn mnhmh poy epiane o student komvos
    free(student);
}

