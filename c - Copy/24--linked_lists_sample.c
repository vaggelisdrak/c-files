#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 50
#define L 50

typedef struct node
{
    float gpa;
    char *name;
    struct node *next;
} Node;

typedef Node Lst; /* Sinwnimo tou komvou listas */
typedef Node *Node_ptr; /* Sinwnimo tou deikti komvou --  NODE_ptr*/ 

//basikes syn
Node *create_node(float gpa,char *name);
void delete_node(Node **head, char onoma[L]);
Node * getNode(Node *head,char onoma[L]);
void printList(Node *head);

//extra syn
Node *get_best_gpaNode(Node *head);
void mesos_oros(Node *head);
void reverse(Node **head);
void insert_in_pos(Node **head,int pos,char onoma[L], float gpa);
void sortlist(Node **head);
void swap(Node *a, Node *b);

int main(void)
{
    Node_ptr head,temp; // head = lst

    FILE *fp;
    float gpa[M];
    char names[M][L];
    int j=0;

    fp = fopen("sample.txt","r");
    if (!fp){exit(0);}

    while (fscanf(fp,"%s %f",names[j],&gpa[j])!=EOF)
    {
        //printf("%s %f", names[j],gpa[j]);
        j++;
    }

    for(int i=0;i<j;i++){
        char *p;
        p = strtok(names[i],"!,.'-?");
        while(p!=NULL){
            strcpy(names[i],p);
            p = strtok(NULL,"!,.'-?");
        }
    }

    /*---------------------------------------------------*/
    head = create_node(gpa[0], names[0]);
    temp = head;
    for(int i=1;i<=j;i++){
        //printf("%s %f\n", temp->name,temp->gpa);
        temp->next = create_node(gpa[i], names[i]);
        temp = temp->next;
        //temp->next = insert_sorted(temp->next, create_node(gpa[i], names[i]));
        /*if (i==j)
        {
            temp->next = NULL;
        }
        else{
            temp = temp->next;
        }*/

    }
    
    sortlist(&head);

    printList(head);
    delete_node(&head, "panos");
    printf("\n");
    printList(head);
    printf("\n");

    char onoma[L+1];
    printf("anazhthse enan mathiti: ");
    scanf("%s",onoma);
    Node * tmp;
    tmp = getNode(head,onoma);
    printf("\no mathitis %s exei gpa %.2f",tmp->name,tmp->gpa);

    Node * best_gpa_std;
    best_gpa_std = get_best_gpaNode(head);
    printf("\no mathitis me to megalytero gpa eina o: %s (%.2f)",best_gpa_std->name,best_gpa_std->gpa);

    mesos_oros(head);

    printf("\n\nreverse order\n\n");
    reverse(&head);
    printList(head);

    printf("\n\ninsert node\n\n");
    insert_in_pos(&head,3,"steve",2.12);
    printList(head);

    return 0;
}

Node *create_node(float gpa, char * name){
    Node *temp;

    temp = (Node *) malloc(sizeof(Node));
    temp->gpa = gpa;
    temp->name = (char *) malloc((strlen(name)+1)*sizeof(char));
    strcpy(temp->name,name);
    temp->next = NULL;

    return temp;
}


Node *getNode(Node * head,char onoma[L]){
    Node *iter;
    for(iter=head;iter!=NULL;iter=iter->next){
        if(strcmp(iter->name,onoma)==0){
            return iter;
        }
    }
    return NULL;
}

void printList(Node *head){
    Node * iter;
    for(iter = head;iter!=NULL;iter = iter->next){
        printf("o mathitis %s exei vathmo %f\n",iter->name,iter->gpa);
    }
    return;
}

void delete_node(Node **head, char onoma[L]){
    Node * node_to_del;
    node_to_del = getNode(*head,onoma);

    if (*head == node_to_del)
        *head = node_to_del->next; // thelo *head oste na mhn allazei mono topika o deikths,alla kai exo apo thn syn.dld passed by reference oxi by value gia ton deikth head
    else
    {
        Node *iter = *head;
        for (; iter != NULL && iter->next != node_to_del; iter = iter->next); // ftano ston komvo prin apo ayton stou student - find previous node
        if (iter != NULL)
            iter->next = node_to_del->next; // allazo ton deikth toy komvoy oste na mhn deixnei ton student komvo alla ton epomeno (ayton poy deixnei o student)
    }
    free(node_to_del->name); // adeiazo thn mnhmh poy epiane o student komvos
    free(node_to_del);
}

Node *get_best_gpaNode(Node *head){
    Node_ptr iter,temp;
    float best_gpa = 0.0;
    for(iter = head;iter!=NULL;iter=iter->next){
        if(iter->gpa > best_gpa){
            best_gpa = iter->gpa;
            temp = iter;
        }
    }
    return temp;
}

void mesos_oros(Node *head){
    Node *iter;
    float total = 0.0;
    int num_of_stds = 0;
    for(iter=head;iter!=NULL;iter=iter->next){
        total = total + iter->gpa;
        num_of_stds++;
    }

    printf("\no mesos oros ton %d mathiton einai %f",num_of_stds,total/num_of_stds);
    return;
}


/* Function to reverse the linked list */
void reverse(Node **head)
{
    Node_ptr prev = NULL;
    Node_ptr current = *head;
    Node_ptr next;
    while (current != NULL)
    {
        next = current->next; //o next deixnei ston epomeno komvo toy torinoy
        current->next = prev; // o deikths tou torinoy komvoy deixnei ston prohgoymeno komvo
        prev = current;       // o prohgoymenos konvos ginetai torinos , dld o prev deixnei ton komvo poy deixnei o current
        current = next; // o torinos konvos ginetai epomenos , dld o current deixnei ton komvo poy deixnei o next
    }
    *head = prev; //o arxikos komvos head pleon deixnei ton teleytaio komnvo 
}

void sortlist(Node **head)
{
    // void bubbleSort
    int swapped;
    Node *current;
    Node *tmp = NULL;

    /* Checking for empty list */
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        current = *head;

        while (current->next != tmp) // mexri to teleytaio node poy exei ginei sorted https://www.youtube.com/watch?v=pdMPvMM12G0
        {
            if (current->gpa < current->next->gpa) //descending order by gpa
            {
                swap(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        tmp = current;
    } while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(Node *a, Node *b)
{
    float temp;
    temp = a->gpa;
    a->gpa = b->gpa;
    b->gpa = temp;

    char *tmp;
    tmp = a->name;
    a->name = b->name;
    b->name = tmp;
}

void insert_in_pos(Node **head, int pos, char onoma[L],float gpa){
    Node *new_node;
    new_node = create_node(gpa,onoma);
    if (pos == 0){return;}
    if (pos == 1){
        new_node->next = *head; // o neos komvos deixnei ekei poy deixnei o head ,dld ston palio proto komvo
        *head = new_node; // o deikths head pleon deixnei sto neo komvo
    }
    else
    {
        Node *itr;
        int total_nodes = 0;
        for (itr = *head; itr != NULL; itr = itr->next)
        {
            total_nodes++;
        }

        if(pos > total_nodes){return;}

        int iter_nodes = 1;
        Node *iter = *head;
        for (; iter != NULL; iter = iter->next){
            if(iter_nodes == pos-1){
                new_node->next = iter->next;
                iter->next = new_node;
                break;
            }
            iter_nodes++;
        }
            
    }
}