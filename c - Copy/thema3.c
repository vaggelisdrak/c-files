#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char *string;
    struct node *next_ptr;
} Node;
typedef Node *T;

Node *create(char *);
T insertsorted(T x, Node *);
void report(T lst);
void s(T x, int *chars);

int main()
{
    T lst = NULL;
    int chars;
    char str[50 + 1];
    FILE *input = fopen("words.txt", "rt");
    while (fscanf(input, "%50s", str) != EOF)
    {
        lst = insertsorted(lst, create(str));
        report(lst);
    }
    s(lst, &chars);
    printf("chars %d\n", chars);
    fclose(input);
    return 0;
}

Node *create(char *str)
{
    Node *temp = malloc(sizeof(Node));
    temp->string = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(temp->string, str);
    temp->next_ptr = NULL;
    return temp;
}

void report(T lst)
{
    if (lst == NULL)
    {
        printf("\n");
        return;
    }
    printf("%s ", lst->string);
    report(lst->next_ptr);
    return;
}

T insertsorted(T x, Node *node_ptr)
{
    if (x == NULL)
        return node_ptr;
    if (node_ptr == NULL)
        return x;
    if (strcmp(x->string, node_ptr->string) > -1)
    {
        node_ptr->next_ptr = x;
        return node_ptr;
    }
    x->next_ptr = insertsorted(x->next_ptr, node_ptr);
    return x;
}

void s(T x, int *chars)
{
    if (x == NULL)
        return;
    *chars += strlen(x->string);
    s(x->next_ptr, chars);
    return;
}
